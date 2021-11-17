#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <main.h>

typedef enum Colour {
	RED = 0b00,
	BLUE = 0b01,
	CLEAR = 0b10,
	GREEN = 0b11
} Colour;

uint8_t getRightColourRaw(UART_HandleTypeDef *huart1);
uint8_t getLeftColourRaw(UART_HandleTypeDef *huart6);
Colour getRightColour(UART_HandleTypeDef *huart1);
Colour getLeftColour(UART_HandleTypeDef *huart6);
void setRightColour(Colour colour);
void setLeftColour(Colour colour);

#endif
