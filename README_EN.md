This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/SoftServo.svg?color=brightgreen)](https://github.com/GyverLibs/SoftServo/releases/latest/download/SoftServo.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/SoftServo.svg)](https://registry.platformio.org/libraries/gyverlibs/SoftServo)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/SoftServo?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# SoftServo
Servo software management library (based on millis/micros)
- Does not use an additional hardware timer
- It runs on millis() and micros()
- Servo syntax. h h
- Working mode asynchronous and with delay

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>

## Installation
- The library can be found under the name **SoftServo** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/SoftServo/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>

## Initialization
```cpp
SoftServo myservo;
```

<a id="usage"></a>

## Use of use
```cpp
static constexpr uint16_t MinPulse = 544;   // default min pulse
static constexpr uint16_t MaxPulse = 2400;  // default max pulse
static constexpr uint16_t DefPulse = 1500;  // default pulse

void setPWMFreq(uint16_t hz);   // set PWM frequency, default 50 Hz
void config(uint16_t minUs, uint16_t maxUs); // set min-max pulses

// attach with min-max pulse and start pulse
void attach(uint8_t pin, uint16_t minUs = MinPulse, uint16_t maxUs = MaxPulse, uint16_t pulse = DefPulse);
void detach();                  // disconnect

void asyncMode();               // switch to async mode
void delayMode();               // switch to delay mode (default)
bool tick();                    // ticker, call as often as possible

void write(uint16_t value, uint16_t maxAngle = 180); // set angle or pulse
void writeMicroseconds(uint16_t us);                 // set pulse width
uint16_t read(uint16_t maxAngle = 180);              // get current angle
uint16_t readMicroseconds();                         // get current pulse

bool attached();                // true if the servo is connected
uint16_t getMinUs();            // get min pulse
uint16_t getMaxUs();            // get max pulse
```

`write(value)` works like `Servo`: if `value <= maxAngle`, the value is treated as an angle and mapped to the current `minUs/maxUs` range. If `value > maxAngle`, the value is treated as a pulse width in microseconds.

In async mode `tick()` does not block for the pulse duration and returns `true` while the pulse is active. In delay mode `tick()` blocks for the pulse duration.

<a id="example"></a>

## Example
For more examples see **examples**!
```cpp
#include "SoftServo.h"

SoftServo myservo;

void setup() {
  myservo.attach(5);
  
  // asyncMode - call tick does not block the code by the pulse value (0.7-2.5 ms)
  // But the work will be unstable if there are delays in the code.
  // In this mode, the tick will return true to the pulse period, you can forbid
  // heavy duty during this period
  myservo.asyncMode();
  
  // delayMode - call tick blocks the code by the pulse value (0.7-2.5 ms) - by default
  myservo.delayMode();  
}

int val = 0;
void loop() {
  // ticker - call as often as possible for each copy
  myservo.tick();
  
  // Let's go there.
  static uint32_t tmr;
  if (millis() - tmr >= 50) {
    tmr = millis();    
    static int dir = 5;
    val += dir;    
    if (val >= 180 || val <= 0) dir = -dir;   // unfold
    myservo.write(val);
  }
}
```

<a id="versions"></a>

## Versions
- v1.0
- v1.1 - redesigned FastIO
- v1.1.1 - FastIO removed
- v1.2 - small fixtures

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
