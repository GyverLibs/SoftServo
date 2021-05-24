/*
    Библиотека для программного управления Servo (на базе millis/micros)
    Документация: 
    GitHub: https://github.com/GyverLibs/SoftServo
    Возможности:
    - Не использует дополнительный аппаратный таймер
    - Работает на millis() и micros()
    - Синтаксис как у Servo.h
    - Режим работы асинхронный и с delay
    - Повышенная произвводительность для AVR
        
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/

#ifndef SoftServo_h
#define SoftServo_h
#include <Arduino.h>
#include "FastIO.h"

class SoftServo {
public:
    // подключить с указанием мин и макс импульса
    void attach(int pin, int min = 500, int max = 2400) {
        _pin = pin;
        pinMode(_pin, OUTPUT);
        _attached = true;
        _min = min;
        _max = max;
    }
    
    // отключить
    void detach() {
        _attached = false;
    }
    
    // переключить в асинхронный режим
    void asyncMode() {
        _mode = true;
    }
    
    // переключить в режим задержки (по умолч)
    void delayMode() {
        _mode = false;
    }
    
    // тикер, вызывать как можно чаще
    // в асинхронном режиме вернёт true во время отработки импульса
    bool tick() {
        if (_attached && millis() - _tmr50 >= 20) {
            if (_mode) {
                if (!_flag) {
                    _tmrUs = micros();
                    _flag = 1;
                    fastWrite(_pin, 1);                    
                } else {
                    if (micros() - _tmrUs >= _us) {
                        fastWrite(_pin, 0);
                        _flag = 0;
                        _tmr50 = millis();
                    } else return true;
                }
            } else {
                _tmr50 = millis();
                fastWrite(_pin, 1);
                delayMicroseconds(_us);
                fastWrite(_pin, 0);
            }
        }
        return false;
    }
    
    // поставить на угол
    void write(int value) {
        if (value < 200) value = map(value, 0, 180, _min, _max);
        writeMicroseconds(value);
    }
    
    // поставить на импульс
    void writeMicroseconds(int us) {
        _us = us;
    }
    
    // вернуть текущий угол
    int read() {
        return map(_us, _min, _max, 0, 180);
    }
    
    // вернуть текущий импульс
    int readMicroseconds() {
        return _us;
    }
    
    // true если серво подключена
    bool attached() {
        return _attached;
    }
    
private:
    uint8_t _pin = 255;
    int _us = 700, _min, _max;
    bool _attached = false, _mode = false, _flag = false;
    uint32_t _tmr50 = 0, _tmrUs = 0;
};
#endif