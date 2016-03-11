#include "GolfBalls.h"

GolfBalls::GolfBalls(int _dispenserMotorPin, int _scoreServoPin)
{
  dispenserMotorPin = _dispenserMotorPin;
  scoreServoPin = _scoreServoPin;
  bool scoring= false;
}

void GolfBalls::startUp()
{
  dispenserMotor.attach(dispenserMotorPin);
  scoreServo.attach(scoreServoPin);

}

void GolfBalls::periodic(ControllerData ctrl)
{

  if (CTRL_DISPENSER_MOTOR) {
    dispenserMotor.write(160);
  }
  else{
    dispenserMotor.write(90);
  }

  if(CTRL_FOAM_BALL_SERVO){
    scoring= true; 
    if (millis() - startScoreTime < 5000){
      scoreServo.write(GOLF_SCORE_POSN);
    }
    else{
    scoring= false;
    scoreServo.write(GOLF_HOLD_POSN);
    }
  }
}

