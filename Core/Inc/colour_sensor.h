#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <main.h>

typedef enum Colour {
	RED = 0b00,
	BLUE = 0b01,
	CLEAR = 0b10,
	GREEN = 0b11,
	NO_COLOUR
} Colour;

void initColourSensors(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart6);
uint8_t getRightColourRaw();
uint8_t getLeftColourRaw();
Colour getRightColour();
Colour getLeftColour();
void setRightColour(Colour colour);
void setLeftColour(Colour colour);

#endif
