#include "Constants.h"
#include "ControllerData.h"
#include "Robot.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_VCNL4010.h>
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial XBee(0, 1); // RX, TX


Robot Rob = Robot(  LEFT_MOTOR_PIN,
                    RIGHT_MOTOR_PIN,
                    MIDDLE_MOTOR_PIN,
                    GYRO_PIN,
                    SHIFTER_PIN,
                    DRIVE_MODE,
                    
                    RELEASER_ARM_PIN,
                    FOAM_BALL_ARM_PIN,
                    FOAM_BALL_SERVO_PIN,
                    
                    DISPENSER_MOTOR_PIN,
                    GOLF_BALL_SERVO_PIN,
                    SORTER_SERVO_PIN,
                    
                    SWING_DOOR_PIN
                 );

ControllerData readBuffer;
int bufferIndex = 0;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);

  Serial.println("Start setup");
  Rob.startUp();
  Serial.println("End setup");

  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(attemptRead()){
    Rob.control(readBuffer);
    //Serial.println("LSX="+readBuffer.driver1.LSX);
  }
  Rob.periodic();
  delay(10);
}

// attempt to read controller
// note that it is very crucial that the serial code is not blocking
// if it is the robot will be unresponsive
bool attemptRead(){
  // return if we have do not have a full controller info message
  if (Serial.available() < 18-bufferIndex){
    //Serial.println("need more data: "+Serial.available());
    return false;
  }
  // read serial and check that 10 bytes were read
  if(Serial.readBytes(&readBuffer.bytes[bufferIndex], 18-bufferIndex) < 18-bufferIndex){
    bufferIndex = 0;
    //Serial.println("didn't read 18");
    return false;
  }
  bufferIndex = 0;
  
  // if the start byte is not first we have a problem
  while(readBuffer.startByte != 255 || readBuffer.stopByte != 254){
    // attempt to recover
    int i;
    for(i=1; i<18; i++)
      if(readBuffer.bytes[i] == 255)
        break;
    if(i >= 18){
      // recovery failed, attempt another read in case we have more bytes in the buffer
      return attemptRead();
    }else{
      // found possible start byte, attempt to read rest of message
      for(int j=i; j<18; j++){
        readBuffer.bytes[j-i] = readBuffer.bytes[j];
      }
      if(Serial.available() >= i){
        // rest of message available
        if(Serial.readBytes(&readBuffer.bytes[18-i], i) < i){
          //Serial.println("didn't read rest of 18");
          return false;
        }
      }else{
        // wait for rest of message
        // we have to check next function call because this function cannot be blocking
        bufferIndex = 18 - i;
        //Serial.println("wait for rest of message");
        return false;
      }
    }
  }

  // finally we have a good message
  return true;
}

