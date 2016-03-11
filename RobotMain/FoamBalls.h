#ifndef FOAM_BALLS_H_
#define FOAM_BALLS_H_

#include "ControllerData.h"
#include "Constants.h"
#include <Servo.h>

class FoamBalls
{
  public:
    FoamBalls(int _releaseArmPin, int _ballArmPin, int _scoreServoPin);
    void startUp();
    void periodic(ControllerData ctrl);

  private:
    int releaseArmPin;
    int ballArmPin;
    
    int scoreServoPin;
    Servo scoreServo;
    
};


#endif

