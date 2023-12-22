This is an automatic translation, may be incorrect in some places. See sources and examples!

# SoftServo
Library for Servo software control (based on Millis/Micros)
- does not use an additional hardware timer
- works on Millis () and micros ()
- syntax like Servo.h
- Asynchronous operating mode and with Delay
- increased producing for avr

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** SoftServo ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/softServo/archive/refs/heads/main.zip) .ZIP archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
SoftServo MyServo;
`` `

<a id="usage"> </a>
## Usage
`` `CPP
Void attach (int pin, int min = 500, int max = 2400);// Connect with min and max pulse
VOID Detach ();// Disable
Void asyncmode ();// switch to asynchronous mode
VOID DELAYMODE ();// switch to delay mode (default)
Bool Tick ();// ticker, call as often as possible, in asynchronous mode will return True while working out a pulse
VOID Write (int Value);// put on a corner
VOID Writemicroseconds (Int US);// put on an impulse
int Read ();// Return the current corner
intMicroseconds ();// Return the current impulse
Bool Attached ();// true if the servo is connected
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include "SoftServo.h"

SoftServo MyServo;

VOID setup () {
  MyServo.attach (5);
  
  // asyncmode - Tick call does not block the code for the value of the pulse (0.7-2.5 ms)
  // But the work will be unstable if there are delays in the code
  // In this mode, Tick will return True for the impulse period, you can prohibit
  // heavy functions for this period
  MyServo.asyncmode ();
  
  // Delaymode - Tick call blocks the code for the value of the pulse (0.7-2.5 ms) - by default
  MyServo.Delaymode ();
}

Int ValCranberries = 0;
VOID loop () {
  // ticker - call as often as possible for each copy
  MyServo.tick ();
  
  // move here
  Static uint32_t tmr;
  if (millis () - tmr> = 50) {
    TMR = Millis ();
    Static inti = 5;
    val += dir;
    if (val> = 180 || val <= 0) die = -dir;// unfold
    MyServo.write (val);
  }
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - Redeled Fastio
- V1.1.1 - removed Fastio
- V1.2 - Small fixes

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code