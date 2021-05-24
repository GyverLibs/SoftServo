#include "SoftServo.h"

SoftServo myservo;

void setup() {
  myservo.attach(5);
  
  // asyncMode - вызов tick не блокирует код на величину импульса (0.7-2.5 мс)
  // но работа будет нестабильной при наличии задержек в коде
  // в этом режиме tick вернёт true на период импульса, можно запрещать
  // тяжёлые функции на этот период 
  myservo.asyncMode();
  
  // delayMode - вызов tick блокирует код на величину импульса (0.7-2.5 мс) - по умолчанию  
  myservo.delayMode();  
}

int val = 0;
void loop() {
  // тикер - вызывать как можно чаще для каждого экземпляра
  myservo.tick();
  
  // двигаем туда сюда
  static uint32_t tmr;
  if (millis() - tmr >= 50) {
    tmr = millis();    
    static int dir = 5;
    val += dir;    
    if (val >= 180 || val <= 0) dir = -dir;   // разворачиваем
    myservo.write(val);
  }
}