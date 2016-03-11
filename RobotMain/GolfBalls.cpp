#include "GolfBalls.h"

GolfBalls::GolfBalls(int _dispenserMotorPin, int _scoreServoPin)
{
  dispenserMotorPin = _dispenserMotorPin;
  scoreServoPin = _scoreServoPin;
  scoring = false;
}

void GolfBalls::startUp()
{
  dispenserMotor.attach(dispenserMotorPin);
  scoreServo.attach(scoreServoPin);

  dispenserMotor.write(90);
  scoreServo.write(GOLF_HOLD_POSN);
}

void GolfBalls::periodic(ControllerData ctrl)
{
  if (CTRL_DISPENSER_MOTOR) {
    dispenserMotor.write(DISPENSE_SPEED);
  }
  else{
    dispenserMotor.write(90);
  }

  if(CTRL_GOLF_BALL_SCORE){
    scoring = true;
    scoreStartTime = millis();
    scoreServo.write(GOLF_SCORE_POSN);
  }
  
  if(scoring && millis()-scoreStartTime > GOLF_HOLD_TIME){
    scoring = false;
    scoreServo.write(GOLF_HOLD_POSN);
  }
}

