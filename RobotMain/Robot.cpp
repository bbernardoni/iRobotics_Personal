#include "Robot.h"

Robot::Robot(int _lD, int _rD, int _mD, int _bArm, int _rArm, int _gbServo, int _fbServo, Drive::DriveMode _mode):
  drive(_lD, _rD, _mD, _mode)
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
  for(int i=1; i<9; i++)
    ctrl.bytes[i] = 0;
}

void Robot::periodic()
{
  drive.periodic();
}

void Robot::control(ControllerData _data)
{
  ctrl = _data;
  drive.control(CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
}

