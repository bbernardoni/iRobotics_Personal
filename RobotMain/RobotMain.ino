#include "Constants.h"
#include "ControllerData.h"
#include "Robot.h"
#include <Servo.h>

Robot Rob = Robot(  LEFT_MOTOR_PIN,
                    RIGHT_MOTOR_PIN,
                    MIDDLE_MOTOR_PIN,
                    FOAM_BALL_ARM_PIN,
                    RELEASER_ARM_PIN,
                    GOLF_BALL_SERVO_PIN,
                    FOAM_BALL_SERVO_PIN,
                    DRIVE_MODE
                 );

ControllerData readBuffer;
int bufferIndex = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  Rob.startUp();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(attemptRead())
    Rob.control(readBuffer);
  Rob.periodic();
  delay(10);
}

// attempt to read controller
// note that it is very crucial that the serial code is not blocking
// if it is the robot will be unresponsive
bool attemptRead(){
  // return if we have do not have a full controller info message
  if (Serial.available() < 10-bufferIndex)
    return false;
  // read serial and check that 10 bytes were read
  if(Serial.readBytes(&readBuffer.bytes[bufferIndex], 10-bufferIndex) < 10-bufferIndex){
    bufferIndex = 0;
    return false;
  }
  bufferIndex = 0;
  
  // if the start byte is not first we have a problem
  while(readBuffer.startByte != 255 || readBuffer.stopByte != 254){
    // attempt to recover
    int i;
    for(i=1; i<10; i++)
      if(readBuffer.bytes[i] == 255)
        break;
    if(i >= 10){
      // recovery failed, attempt another read in case we have more bytes in the buffer
      return attemptRead();
    }else{
      // found possible start byte, attempt to read rest of message
      for(int j=i; j<10; j++){
        readBuffer.bytes[j-i] = readBuffer.bytes[j];
      }
      if(Serial.available() >= i){
        // rest of message available
        if(Serial.readBytes(&readBuffer.bytes[10-i], i) < i)
          return false;
      }else{
        // wait for rest of message
        // we have to check next function call because this function cannot be blocking
        bufferIndex = 10 - i;
        return false;
      }
    }
  }

  // finally we have a good message
  return true;
}

