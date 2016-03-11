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
//toggling of the dispenser motor
  digitalWrite(dispenserMotorPin, CTRL_DISPENSER_MOTOR ? HIGH : LOW);
  if (CTRL_DISPENSER_MOTOR == HIGH) {
    analogWrite(dispenserMotorPin, 160);
  }
  else
    analogWrite(dispenserMotorPin, 90);
    
  //digitalWrite(scoreServoPin, CTRL_GOLF_BALL_SERVO? HIGH: LOW);

  // I used this to control the golf ball release servo -ALEC
  switch (ctrl.driver2.start) {
    case 1:
      scoreServo.write(GOLF_SCORE_POSN);
      delay(5000);
      break;
    case 0:
      scoreServo.write(GOLF_HOLD_POSN);
      break;

  }

}

