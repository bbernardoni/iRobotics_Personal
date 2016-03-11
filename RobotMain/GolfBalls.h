#ifndef GOLF_BALLS_H_
#define GOLF_BALLS_H_

#include "ControllerData.h"
#include "Constants.h"
#include <Servo.h>

class GolfBalls
{
  public:
    GolfBalls(int _dispenserMotorPin, int _scoreServoPin);
    void startUp();
    void periodic(ControllerData ctrl);

  private:
    int dispenserMotorPin;
    Servo dispenserMotor;
    int scoreServoPin;
    Servo scoreServo;
    unsigned long scoreStartTime;
    bool scoring;
    
};


#endif

