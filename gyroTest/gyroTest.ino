
#include <SPI.h>

int result;
int result2;
int Gyro1;

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(7, OUTPUT);
  digitalWrite(7,HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
  delay(100);

}

void loop() {


  digitalWrite(7, LOW);
  result = SPI.transfer(0x20);
  result = result << 8 | SPI.transfer(0x00);
  result2 = SPI.transfer(0x00) >>2;
  SPI.transfer(0x00);
  result = result << 6 | result2;
  digitalWrite(7, HIGH);  

  Gyro1 = (Gyro1)*0.5 + result*(1 - 0.5);

  Serial.println(Gyro1);

}
