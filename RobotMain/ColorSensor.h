#ifndef COLORSENSOR_H_
#define COLORSENSOR_H_

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "Constants.h"
#include "Sorter.h"

class ColorSensor
{
public:
	int ColorValues(int correctTemperature);
private:
	uint16_t r, g, b, c, colorTemp, lux;	
};

#endif