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
*/

#pragma once
#include <Arduino.h>
#include <GyverIO.h>

#define SSERVO_PERIOD 20

class SoftServo {
   public:
    SoftServo() {}

    SoftServo(const uint8_t pin, uint16_t minus = 500, uint16_t maxus = 2400) {
        attach(pin, minus, maxus);
    }

    // подключить с указанием мин и макс импульса
    void attach(const uint8_t pin, uint16_t minus = 500, uint16_t maxus = 2400) {
        _pin.init(pin, OUTPUT);
        _attached = true;
        _min = minus;
        _max = maxus;
    }

    // подключить на старый пин
    void attach() {
        if (_pin.valid()) _attached = true;
    }

    // отключить
    void detach() {
        _attached = false;
    }

    // переключить в асинхронный режим
    void asyncMode() {
        _async = true;
    }

    // переключить в режим задержки (по умолч)
    void delayMode() {
        _async = false;
    }

    // тикер, вызывать как можно чаще
    // в асинхронном режиме вернёт true во время отработки импульса
    bool tick() {
        if (_tmrUs) {
            if (uint16_t(uint16_t(micros()) - _tmrUs) >= _us) {
                _pin.low();
                _tmrUs = 0;
            }
            return true;

        } else if (_attached && uint16_t(uint16_t(millis()) - _tmr50) >= SSERVO_PERIOD) {
            _tmr50 = millis();
            if (_async) {
                _pin.high();
                _tmrUs = micros();
                if (!_tmrUs) --_tmrUs;
            } else {
                _pin.high();
                delayMicroseconds(_us);
                _pin.low();
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
    gio::PinIO _pin;
    uint16_t _us = 700, _min, _max;
    uint16_t _tmr50 = 0, _tmrUs = 0;
    bool _attached = false, _async = false;
};