#include "Drive.h"

Drive::Drive(int _lD, int _rD, int _mD, int _gyroPin, int _shifterPin, DriveMode _mode)
{
  rD = _rD;
  lD = _lD;
  mD = _mD;
  gyroPin = _gyroPin;
  shifterPin =  _shifterPin;
  mode = _mode;
}

void Drive::startUp()
{
  leftMotors.attach(lD);
  rightMotors.attach(rD);
  centerMotor.attach(mD);
  
  SPI.begin();
  pinMode(gyroPin, OUTPUT);
  digitalWrite(gyroPin, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
  lastGyroRead = 0;
  gyroOffset = 0.0;

  pinMode(shifterPin, OUTPUT);
  digitalWrite(shifterPin, LOW);
}

void Drive::periodic(ControllerData ctrl)
{
  digitalWrite(shifterPin, CTRL_SHIFT? HIGH: LOW);
  
  switch(mode){
  case fieldCentric:
    fieldCentricControl(CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);

    if(CTRL_GYRO_RESET){
      gyroOffset = gyroAngle;
    }
    if(CTRL_GYRO_ROT_CCW){
      gyroOffset += PI/2.0;
    }
    if(CTRL_GYRO_ROT_CW){
      gyroOffset -= PI/2.0;
    }
    break;
  case robotCentric:
    robotCentricControl(CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
    break;
  }
}

void Drive::fieldCentricControl(double transX, double transY, double rot){
  double robX = 0.0;
  double robY = 0.0;
  double robAngle = getGyroAngle();
  //Serial.println(robAngle);

  if(transX != 0.0 && transY != 0.0){
    double transAngle = PMod(atan2(transY, transX) - robAngle, PI*2.0);
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
  rightMotors.write(Rev(SOut(rSpeed)));
  centerMotor.write(Rev(SOut(transX)));
}

// return the current angle (radians) the robot is facing
// 0 is forward and counter clockwise is positive
double Drive::getGyroAngle(){
  unsigned long readTime = micros();
  if(lastGyroRead == 0)
    lastGyroRead = readTime;
  
  digitalWrite(gyroPin, LOW);
  int result = SPI.transfer(0x20);
  result = result << 8 | SPI.transfer(0x00);
  int result2 = SPI.transfer(0x00) >>2;
  SPI.transfer(0x00);
  result = result << 6 | result2;
  digitalWrite(gyroPin, HIGH);

  // low pass filter
  gyroSpeed = (gyroSpeed)*0.5 + result*(1 - 0.5);
  // gyro returns in units of 80 LSB/deg/sec

  if(abs(gyroSpeed) > 40){
    gyroAngle += gyroSpeed/80.0*(readTime-lastGyroRead)/1000000.0;
    //Serial.println(gyroSpeed);
  }
  lastGyroRead = readTime;
  
  return PMod(gyroAngle - gyroOffset, PI*2.0);
}
