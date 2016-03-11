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
  
  pinMode(releaseArmPin, OUTPUT);
  digitalWrite(releaseArmPin, LOW);
  pinMode(ballArmPin, OUTPUT);
  digitalWrite(ballArmPin, LOW);
  
  scoreServo.write(FOAM_HOLD_POSN);
}

void FoamBalls::periodic(ControllerData ctrl)
{
  digitalWrite(releaseArmPin, CTRL_RELEASE_ARM? HIGH: LOW);
  digitalWrite(ballArmPin, CTRL_FOAM_BALL_ARM? HIGH: LOW);
  
  //Scores the foam balls via the servo
  if(CTRL_FOAM_BALL_SCORE){
    scoring = true;
    scoreStartTime = millis();
    scoreServo.write(FOAM_SCORE_POSN);
  }
  
  if(scoring && millis()-scoreStartTime > 4000){
    scoring = false;
    scoreServo.write(FOAM_HOLD_POSN);
  }
}

