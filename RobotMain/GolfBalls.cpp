#include "GolfBalls.h"

GolfBalls::GolfBalls(int _dispenserMotorPin, int _scoreServoPin)
{
  dispenserMotorPin = _dispenserMotorPin;
  scoreServoPin = _scoreServoPin;
}

void GolfBalls::startUp()
{
  dispenserMotor.attach(dispenserMotorPin);
  scoreServo.attach(scoreServoPin);
}

void GolfBalls::periodic(ControllerData ctrl)
{
  if(ctrl.driver2.start==1){
    scoreServo.write(180);
    } 
  else
    scoreServo.write(0);
}

