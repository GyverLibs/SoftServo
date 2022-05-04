This is an automatic translation, may be incorrect in some places. See sources and examples!

# softservo
Servo control library (millis/micros based)
- Does not use additional hardware timer
- Works on millis() and micros()
- Same syntax as Servo.h
- Operating mode asynchronous and with delay
- Improved performance for AVR

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **SoftServo** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/SoftServo/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
Softservo myservo;
```

<a id="usage"></a>
## Usage
```cpp
void attach(int pin, int min = 500, int max = 2400); // connect with min and max pulse
void detach(); // disable
void asyncMode(); // switch to asynchronous mode
void delayMode(); // switch to delay mode (default)
bool tick(); // ticker, call as often as possible, in asynchronous mode will return true during the execution of the impulse
void write(int value); // put on corner
void writeMicroseconds(int us); // put on impulse
intread(); // return current angle
int readMicroseconds(); // return current pulse
bool attached(); // true if servo is connected
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include "Softservo.h"

Softservo myservo;

void setup() {
  myservo.attach(5);
  
  // asyncMode - calling tick does not block the code for the amount of the pulse (0.7-2.5 ms)
  // but the work will be unstable if there are delays in the code
  // in this mode, tick will return true for the period of the pulse, you can disable
  // heavy functions for this period
  myservo.asyncMode();
  
  // delayMode - calling tick blocks the code for the amount of the pulse (0.7-2.5 ms) - by default
  myservo.delayMode();
}

intval = 0;
void loop() {
  // ticker - call as often as possible for each instance
  myservo.tick();
  
  // move back and forth
  static uint32_t tmr;
  if (millis() - tmr >= 50) {
    tmr = millis();
    static int dir = 5;
    val += dir;
    if (val >= 180 || val <= 0) dir = -dir; // expand
    myservo.write(val);
  }
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - redesigned FastIO
- v1.1.1 - removed FastIO

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!