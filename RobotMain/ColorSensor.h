#ifndef COLORSENSOR_H_
#define COLORSENSOR_H_

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "Constants.h"

class ColorSensor
{
public:
	void ColorValues();
private:
	uint16_t r, g, b, c, colorTemp, lux;	
}