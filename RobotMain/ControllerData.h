#ifndef CONTROLLER_DATA_H_
#define CONTROLLER_DATA_H_

#include "Arduino.h"

union ControllerData {
  struct{
    byte startByte;
    bool start : 1;
    bool rightBumper : 1;
    bool leftBumper : 1;
    bool y : 1;
    bool x : 1;
    bool b : 1;
    bool a : 1;
    bool : 1;
    bool back : 1;
    bool rightClick : 1;
    bool leftClick : 1;
    bool dRight : 1;
    bool dLeft : 1;
    bool dDown : 1;
    bool dUp : 1;
    bool : 1;
    byte LSX;
    byte LSY;
    byte RSX;
    byte RSY;
    byte LTG;
    byte RTG;
    byte stopByte;
  };
  byte bytes[10];
};

#endif

