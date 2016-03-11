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
  
  pinMode(dispenserMotorPin, OUTPUT);
  digitalWrite(dispenserMotorPin, LOW);
  pinMode(scoreServoPin, OUTPUT);
  digitalWrite(scoreServoPin, LOW);
}

void GolfBalls::periodic(ControllerData ctrl)
{
  digitalWrite(dispenserMotorPin, CTRL_DISPENSER_MOTOR? HIGH: LOW);
  digitalWrite(scoreServoPin, CTRL_GOLF_BALL_SERVO? HIGH: LOW);
}

