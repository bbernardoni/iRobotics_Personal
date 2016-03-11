#ifndef SORTER_H_
#define SORTER_H_

#include "ControllerData.h"
#include "Constants.h"
#include <Servo.h>




class Sorter
{
  public:
    enum SorterState { neutral, accept, reject };
    SorterState state;
    Sorter(int _sorterServoPin);
    void startUp();
    void periodic(ControllerData ctrl);

  private:
    int sorterServoPin;
    Servo sorterServo;
/*
    Adafruit_VCNL4010 vcnl;
    Adafruit_TCS34725 tcs;*/

    
    unsigned long startSortTime;
};


#endif

