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
  //Scores the foam balls via the servo
  switch(ctrl.driver2.back){
    case 1:
    if(millis()-startScoreTime<5000){
      scoreServo.write(FOAM_SCORE_POSN);
    }
    scoreServo.write(FOAM_HOLD_POSN);
      break;
    case 0:
      scoreServo.write(FOAM_HOLD_POSN);
    }
}

