#ifndef ROBOT_H_
#define ROBOT_H_

#include "Arduino.h"
#include "Drive.h"
#include "FoamBalls.h"
#include "GolfBalls.h"
#include "Sorter.h"
#include "SwingDoor.h"
#include "ControllerData.h"
#include "Constants.h"

class Robot
{
  public:
    Robot(int _lD, int _rD, int _mD, int _gyroPin, int _shifterPin, Drive::DriveMode _mode,
          int _releaseArmPin, int _ballArmPin, int _scoreFoamServoPin,
          int _dispenserMotorPin, int _scoreGolfServoPin, int _sorterServoPin,
          int _swingDoorPin
          );
    void startUp();
    void periodic();

    void control(ControllerData _data);

  private:
    ControllerData ctrl;
    Drive drive;
    FoamBalls foamBalls;
    GolfBalls golfBalls;
    Sorter sorter;
    SwingDoor swingDoor;
};


#endif

