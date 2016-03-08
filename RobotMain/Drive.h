#ifndef DRIVE_H_
#define DRIVE_H_

#include <Servo.h>
#include "Arduino.h"
#include "ControllerData.h"
#include "Constants.h"
#include <SPI.h>

class Drive
{
  public:
    enum DriveMode { fieldCentric, robotCentric };
    
    Drive(int _lD, int _rD, int _mD, int _gyroPin, DriveMode _mode);
    void startUp();
    void periodic(ControllerData ctrl);
    void control(double transX, double transY, double rot);
    
    // Positive Modulus (n%i)
    static double PMod(double n, double i) { return n-i*floor(n/i); }
    // converts from [-1.0, 1.0] to [0,180] for servo write
    static int SOut(double out) { return int((out+1.0)*90.0); }

  private:
    void fieldCentricControl(double transX, double transY, double rot);
    void robotCentricControl(double transX, double transY, double rot);

    double getGyroAngle();
    
    Servo leftMotors;
    Servo rightMotors;
    Servo centerMotor;
    int rD;
    int lD;
    int mD;

    double transX;
    double transY;
    double rot;

    DriveMode mode;

    int gyroPin;
    unsigned long lastGyroRead;
    unsigned long gyroSpeed;
    unsigned long gyroAngle;
    
};


#endif

