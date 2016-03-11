#include "FoamBalls.h"

FoamBalls::FoamBalls(int _releaseArmPin, int _ballArmPin, int _scoreServoPin)
{
  releaseArmPin = _releaseArmPin;
  ballArmPin = _ballArmPin;
  scoreServoPin = _scoreServoPin;
}

void FoamBalls::startUp()
{
  scoreServo.attach(scoreServoPin);
  
  pinMode(releaseArmPin, OUTPUT);
  digitalWrite(releaseArmPin, LOW);
  pinMode(ballArmPin, OUTPUT);
  digitalWrite(ballArmPin, LOW);
}

void FoamBalls::periodic(ControllerData ctrl)
{
  digitalWrite(releaseArmPin, CTRL_RELEASE_ARM? HIGH: LOW);
  digitalWrite(ballArmPin, CTRL_FOAM_BALL_ARM? HIGH: LOW);
}

