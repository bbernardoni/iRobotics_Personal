#include "FoamBalls.h"

FoamBalls::FoamBalls(int _releaseArmPin, int _ballArmPin, int _scoreServoPin)
{
  releaseArmPin = _releaseArmPin;
  ballArmPin = _ballArmPin;
  scoreServoPin = _scoreServoPin;
  
  scoring = false;
}

void FoamBalls::startUp()
{
  scoreServo.attach(scoreServoPin);
  releaseServo.attach(releaseArmPin);
  
  pinMode(ballArmPin, OUTPUT);
  digitalWrite(ballArmPin, LOW);
  
  scoreServo.write(FOAM_HOLD_POSN);
  releaseServo.write(90);
}

void FoamBalls::periodic(ControllerData ctrl)
{
  double releaseSpeed = 90;
  if(CTRL_RELEASE_ARM > 0) // Up
    releaseSpeed = 90 - 20*CTRL_RELEASE_ARM;
  else if(CTRL_RELEASE_ARM < 0) // Down
    releaseSpeed = 90 - 10*CTRL_RELEASE_ARM;
  releaseServo.write(releaseSpeed);
  
  digitalWrite(ballArmPin, CTRL_FOAM_BALL_ARM? LOW: HIGH);
  
  //Scores the foam balls via the servo
  if(CTRL_FOAM_BALL_SCORE){
    scoring = true;
    scoreStartTime = millis();
    scoreServo.write(FOAM_SCORE_POSN);
  }
  
  if(scoring && millis()-scoreStartTime > FOAM_HOLD_TIME){
    scoring = false;
    scoreServo.write(FOAM_HOLD_POSN);
  }
}

