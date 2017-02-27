#include "Sorter.h"

Sorter::Sorter(int _sorterServoPin):
  tcs(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X),
  vcnl()
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
  if(CTRL_ROBOT_GREEN){
    robotColor = green;
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
        state = dwell;
        startDwellTime = millis();
    }
    break;
  case dwell:
    if(millis() - startDwellTime > SORTER_DWELL_TIME){
      Sorter::Color c = readColor();
      Serial.print("readcolor="); Serial.println(c, DEC);
      if(c == robotColor){
        sorterServo.write(SORTER_ACCEPT_POSN);
        state = accept;
      }else{
        sorterServo.write(SORTER_REJECT_POSN);
        state = reject;
      }
      startSortTime = millis();
    }
    break;
  case accept:
    if(millis() - startSortTime > SORTER_ACCEPT_TIME){
      sorterServo.write(SORTER_NEUTRAL_POSN);
      state = neutral;
    }
    break;
  case reject:
    if(millis() - startSortTime > SORTER_REJECT_TIME){
      sorterServo.write(SORTER_NEUTRAL_POSN);
      state = neutral;
    }
    break;
  }
}

//true if ball close to proximity sensor
bool Sorter::golfballClose()
{
  if (vcnl.readProximity() > PROX_CLOSE) 
  {
    return true;
  }
  return false;
}

void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
} 

//return a color that most closely matches ball rolling in
Sorter::Color Sorter::readColor()
{
  uint16_t r,g,b,c;
  double distanceRed, distanceGreen, distanceWhite, distanceYellow, minDistance;
  Color bestColor;
  tcs.getRawData(&r,&g,&b,&c);
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.println(" ");
  distanceRed = pow((float)(r-RED_R),2.0f) + pow((float)(g-RED_G),2.0f) + pow((float)(b-RED_B),2.0f);
  distanceGreen = pow((float)(r-GREEN_R),2.0f) + pow((float)(g-GREEN_G),2.0f) + pow((float)(g-GREEN_B),2.0f);
  distanceWhite = pow((float)(r-WHITE_R),2.0f) + pow((float)(g-WHITE_G),2.0f) + pow((float)(b-WHITE_B),2.0f);
  distanceYellow = pow((float)(r-YELLOW_R),2.0f) + pow((float)(g-YELLOW_G),2.0f) + pow((float)(b-YELLOW_B),2.0f);
  Serial.print("dR: "); printDouble(distanceRed, 1000); Serial.print(" ");
  Serial.print("dG: "); printDouble(distanceGreen, 1000); Serial.print(" ");
  Serial.print("dW: "); printDouble(distanceWhite, 1000); Serial.print(" ");
  Serial.print("dy: "); printDouble(distanceYellow, 1000); Serial.println(" ");
  bestColor = red;
  minDistance = distanceRed;
  if (distanceGreen < minDistance) {
    bestColor = green;
    minDistance = distanceGreen;
  }
  if (distanceWhite < minDistance) {
    bestColor = white;
    minDistance = distanceWhite;
  }
  if (distanceYellow < minDistance) {
    bestColor = yellow;
    minDistance = distanceYellow;
  }
  return bestColor;
}

