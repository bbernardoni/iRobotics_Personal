#include "Sorter.h"

Sorter::Sorter(int _sorterServoPin):
  tcs(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X)
{
  sorterServoPin = _sorterServoPin;
  state = neutral;
  robotColor = red;
}

void Sorter::startUp()
{
  sorterServo.attach(sorterServoPin);
  sorterServo.write(SORTER_NEUTRAL_POSN);
  tcs.begin();
  vcnl.begin();
}

void Sorter::periodic(ControllerData ctrl)
{
  if(CTRL_ROBOT_RED){
    robotColor = red;
  }
  if(CTRL_ROBOT_BLUE){
    robotColor = blue;
  }
  if(CTRL_ROBOT_WHITE){
    robotColor = white;
  }
  if(CTRL_ROBOT_YELLOW){
    robotColor = yellow;
  }
  switch(state){
  case neutral:
    if(golfballClose()){
      if(readColor() == robotColor){
        sorterServo.write(SORTER_ACCEPT_POSN);
        state = accept;
      }else{
        sorterServo.write(SORTER_REJECT_POSN);
        state = reject;
      }
    }
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

bool Sorter::golfballClose()
{
  return true;
}

Sorter::Color Sorter::readColor()
{
  return red;
}

/*

    enum Colors { red, blue, white, yellow };
    
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
