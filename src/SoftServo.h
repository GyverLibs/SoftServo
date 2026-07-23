#pragma once
#include <Arduino.h>

class SoftServo {
   public:
    static constexpr uint16_t MinPulse = 544;
    static constexpr uint16_t MaxPulse = 2400;
    static constexpr uint16_t DefPulse = 1500;

    // установить частоту ШИМ (умолч. 50 Гц)
    void setPWMFreq(uint16_t hz) {
        if (!hz) hz = 1;
        _pwmPrd = 1000 / hz;
    }

    // установить min-max импульсы
    void config(uint16_t minUs, uint16_t maxUs) {
        _minUs = minUs;
        _maxUs = maxUs;
    }

    // подключить с указанием мин и макс импульса
    void attach(uint8_t pin, uint16_t minUs = MinPulse, uint16_t maxUs = MaxPulse, uint16_t pulse = DefPulse) {
        detach();
        _pin = pin;
        pinMode(_pin, OUTPUT);
        config(minUs, maxUs);
        writeMicroseconds(pulse);
    }

    // отключить
    void detach() {
        if (attached()) {
            pinMode(_pin, INPUT);
            digitalWrite(_pin, LOW);
        }
        _tmrOff = 0;
        _pin = noPin;
    }

    // переключить в асинхронный режим
    void asyncMode() {
        _async = true;
    }

    // переключить в режим задержки (по умолч.)
    void delayMode() {
        _async = false;
    }

    // тикер, вызывать как можно чаще
    // в асинхронном режиме вернёт true во время отработки импульса
    bool tick() {
        if (!attached()) return false;

        if (_tmrOff) {
            if (uint16_t(uint16_t(micros()) - _tmrOff) >= _us) {
                digitalWrite(_pin, LOW);
                _tmrOff = 0;
            }
            return true;
        }

        if (uint16_t(uint16_t(millis()) - _tmrPwm) >= _pwmPrd) {
            _tmrPwm = millis();
            if (_async) {
                digitalWrite(_pin, HIGH);
                _tmrOff = micros();
                if (!_tmrOff) --_tmrOff;
                return true;
            } else {
                digitalWrite(_pin, HIGH);
                delayMicroseconds(_us);
                digitalWrite(_pin, LOW);
            }
        }

        return false;
    }

    // система в асинхронном ожидании
    bool busy() const {
        return _tmrOff != 0;
    }

    // поставить на угол или импульс
    void write(uint16_t value, uint16_t maxAngle = 180) {
        if (!maxAngle) maxAngle = 1;
        if (value <= maxAngle) value = map(value, 0, maxAngle, _minUs, _maxUs);
        writeMicroseconds(value);
    }

    // поставить на импульс
    void writeMicroseconds(uint16_t us) {
        _us = constrain(us, _minUs, _maxUs);
    }

    // вернуть текущий угол
    uint16_t read(uint16_t maxAngle = 180) const {
        return map(_us, _minUs, _maxUs, 0, maxAngle);
    }

    // вернуть текущий импульс
    uint16_t readMicroseconds() const {
        return _us;
    }

    // true если серво подключена
    bool attached() const {
        return _pin != noPin;
    }

    // получить мин импульс
    uint16_t getMinUs() const {
        return _minUs;
    }

    // получить макс импульс
    uint16_t getMaxUs() const {
        return _maxUs;
    }

   private:
    static constexpr uint8_t noPin = 0xff;

    uint16_t _minUs = MinPulse, _maxUs = MaxPulse;
    uint16_t _us = DefPulse;
    uint16_t _tmrPwm = 0, _tmrOff = 0;
    uint16_t _pwmPrd = 20;
    uint8_t _pin = noPin;
    bool _async = false;
};
