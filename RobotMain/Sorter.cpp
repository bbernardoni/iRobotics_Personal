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

//true if ball close to proximity sensor
bool Sorter::golfballClose()
{
  if (vcnl.readProximity() < PROX_CLOSE) {
    return true;
  }
  return false;
}

//return a color that most closely matches ball rolling in
Sorter::Color Sorter::readColor()
{
  uint16_t r,g,b,c;
  double distanceRed, distanceGreen, distanceWhite, distanceYellow, minDistance;
  Color bestColor;
  tcs.getRawData(&r,&g,&b,&c);
  distanceRed = pow(r-RED_R,2) + pow(g-RED_G,2) + pow(b-RED_B,2);
  distanceGreen = pow(r-GREEN_R,2) + pow(g-GREEN_G,2) + pow(g-GREEN_B,2);
  distanceWhite = pow(r-WHITE_R,2) + pow(g-WHITE_G,2) + pow(b-WHITE_B,2);
  distanceYellow = pow(r-YELLOW_R,2) + pow(g-YELLOW_G,2) + pow(b-YELLOW_B,2);
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

