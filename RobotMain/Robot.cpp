#include "Robot.h"

Robot::Robot(int _lD, int _rD, int _mD, int _gyroPin, int _shifterPin,
             int _bArm, int _rArm, int _gbServo, int _fbServo, 
             Drive::DriveMode _mode):
  drive(_lD, _rD, _mD, _gyroPin, _shifterPin, _mode)
{
  bArm = _bArm;
  rArm = _rArm;
  gbServo = _gbServo;
  fbServo = _fbServo;
}

void Robot::startUp()
{
  drive.startUp();
  ctrl.startByte = 255;
  ctrl.stopByte = 254;
  for(int i=1; i<17; i++)
    ctrl.bytes[i] = 0;
}

void Robot::periodic()
{
  drive.periodic(ctrl);
}

void Robot::control(ControllerData _data)
{
  ctrl = _data;
}

