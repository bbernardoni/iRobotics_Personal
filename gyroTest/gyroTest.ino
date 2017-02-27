
#include <SPI.h>

int result;
int result2;
int Gyro1;
double ang;
unsigned long lastRead;
unsigned long readTime;

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(53, OUTPUT);
  digitalWrite(53,HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
  delay(100);
  lastRead = micros();
}

void loop() {


  digitalWrite(53, LOW);
  result = SPI.transfer(0x20);
  result = result << 8 | SPI.transfer(0x00);
  result2 = SPI.transfer(0x00) >>2;
  SPI.transfer(0x00);
  result = result << 6 | result2;
  digitalWrite(53, HIGH);  

  Gyro1 = (Gyro1)*0.5 + result*(1 - 0.5);
  readTime = micros();
  ang += Gyro1/80.0*(readTime-lastRead)/1000000.0;
  lastRead = readTime;

  Serial.println(ang);
  delay(10);
 
}
