#include "Sorter.h"

Sorter::Sorter(int _sorterServoPin)//:
//  tcs(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X)
{
  sorterServoPin = _sorterServoPin;
  state = neutral;
}

void Sorter::startUp()
{
  sorterServo.attach(sorterServoPin);
  //tcs.begin();
  //vcnl.begin();
}

void Sorter::periodic(ControllerData ctrl)
{
  switch(state){
  case neutral:
    
    break;
  case accept:
    if(millis() - startSortTime > 2000){
      sorterServo.write(SORTER_NEUTRAL_POSN);
      state = neutral;
    }
    break;
  case reject:
    if(millis() - startSortTime > 2000){
      sorterServo.write(SORTER_NEUTRAL_POSN);
      state = neutral;
    }
    break;
  }
}
/*

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.print("Ambient: "); Serial.println(vcnl.readAmbient()); //nears a value of 0 with an object that's close
   Serial.print("Proimity: "); Serial.println(vcnl.readProximity()); //increases exponentially when an object nears sensor
   delay(100);
}*/
