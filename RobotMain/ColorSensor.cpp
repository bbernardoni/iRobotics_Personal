/*#include "ColorSensor.h"

ColorSensor::ColorSensor(){}
void ColorSensor::ColorValues(){
  Serial.begin(57600);
  delay(1);
}
  //tcs.getRawData(&r, &g, &b, &c);
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  //lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");

  if(r>1 && r<255 && g>1 && g<255 && b>1 && b<255)
  		state = accept;
  else
  		state = reject;
}
*/
