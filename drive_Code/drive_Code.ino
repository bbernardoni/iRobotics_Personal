// This is some test code for driving
#include <Servo.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

// return the current angle (radians) the robot is facing
// 0 is forward and counter clockwise is positive
double getGyroAngle(){
  // add code to read gyro
  return 0.0;
}

//Positive Modulus (n%i)
static double PMod(double n, double i) {
  return n-i*floor(n/i);
}

void fieldCentricControl(double transX, double transY, double rot){
  double transAngle = PMod(atan2(transY, transX) - getGyroAngle(), PI*2.0);
  double transMag = (fabs(transX) > fabs(transY))? fabs(transX): fabs(transY);
  
  double robX;
  double robY;
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
  
  robotCentricControl(robX, robY, rot);
}

void robotCentricControl(double transX, double transY, double rot){
  // May need to add steer control like: rot *= (1-(1-m_tssr)*transMag);

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
    
  //LeftMotor.set(lSpeed);
  //RightMotor.set(rSpeed);
  //CenterMotor.set(transX);
}

