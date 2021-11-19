#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <main.h>

typedef enum Colour {
	RED = 0b00,
	BLUE = 0b01,
	CLEAR = 0b10,
	GREEN = 0b11,
	BLACK,
	NO_COLOUR
} Colour;

typedef struct {
	float red;
	float green;
	float blue;
	float clear;
} Frequency;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} RGB;

void initColourSensors(TIM_HandleTypeDef* htim4);

float getRightColourFrequency();
void getRightColourIntensities(Frequency *freq);
void getRightRGB(RGB *rgb);
Colour getRightColour();

float getLeftColourFrequency();
void getLeftColourIntensities(Frequency *freq);
void getLeftRGB(RGB *rgb);
Colour getLeftColour();

void setRightColour(Colour colour);
void setLeftColour(Colour colour);

#endif
