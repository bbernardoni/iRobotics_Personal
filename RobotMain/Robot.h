#ifndef ROBOT_H_
#define ROBOT_H_

#include "Arduino.h"
#include "Drive.h"
#include "ControllerData.h"
#include "Constants.h"

class Robot
{
  public:
    Robot(int _lD, int _rD, int _mD, int _gyroPin, 
          int _bArm, int _rArm, int _gbServo, int _fbServo, 
          Drive::DriveMode _mode);
    void startUp();
    void periodic();

    void control(ControllerData _data);

  private:
    ControllerData ctrl;
    Drive drive;
    
    int bArm;
    int rArm;
    int gbServo;
    int fbServo;
};


#endif

