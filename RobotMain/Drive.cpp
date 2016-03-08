#include "Drive.h"

Drive::Drive(int _lD, int _rD, int _mD, DriveMode _mode)
{
  rD = _rD;
  lD = _lD;
  mD = _mD;
  mode = _mode;

  transX = 0.0;
  transY = 0.0;
  rot = 0.0;
}

void Drive::startUp()
{
  leftMotors.attach(lD);
  rightMotors.attach(rD);
  centerMotor.attach(mD);
}

void Drive::control(double _transX, double _transY, double _rot){
  transX = _transX;
  transY = _transY;
  rot = _rot;
}

void Drive::periodic(ControllerData ctrl)
{
  switch(mode){
  case fieldCentric:
    fieldCentricControl(CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
    break;
  case robotCentric:
    robotCentricControl(CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
    break;
  }
}

// return the current angle (radians) the robot is facing
// 0 is forward and counter clockwise is positive
double getGyroAngle(){
  // add code to read gyro
  return 0.0;
}

void Drive::fieldCentricControl(double transX, double transY, double rot){
  double robX = 0.0;
  double robY = 0.0;

  if(transX != 0.0 && transY != 0.0){
    double transAngle = PMod(atan2(transY, transX) - getGyroAngle(), PI*2.0);
    double transMag = (fabs(transX) > fabs(transY))? fabs(transX): fabs(transY);
    
    if(transAngle < PI/4.0 || transAngle > 7.0*PI/4.0){ // positive X is max
      robX = transMag;
      robY = robX*tan(transAngle);
    }else if(transAngle < 3.0*PI/4.0){ // positive Y is max
      robY = transMag;
      robX = robY/tan(transAngle);
    }else if(transAngle < 5.0*PI/4.0){ // negative X is max
      robX = -transMag;
      robY = robX*tan(transAngle);
    }else{ // negative Y is max
      robY = -transMag;
      robX = robY/tan(transAngle);
    }
  }
  
  robotCentricControl(robX, robY, rot);
}

void Drive::robotCentricControl(double transX, double transY, double rot){
  /* May need to add steer control like:
  double transMag = (fabs(transX) > fabs(transY))? fabs(transX): fabs(transY);
  rot *= (1-(1-m_tssr)*transMag);
   */
   
  double lSpeed = transY + rot;
  double rSpeed = transY - rot;
  if(lSpeed < -1.0)
    lSpeed = -1.0;
  if(lSpeed > 1.0)
    lSpeed = 1.0;
  if(rSpeed < -1.0)
    rSpeed = -1.0;
  if(rSpeed > 1.0)
    rSpeed = 1.0;

  leftMotors.write(SOut(lSpeed));
  rightMotors.write(SOut(rSpeed));
  centerMotor.write(SOut(transX));
}
