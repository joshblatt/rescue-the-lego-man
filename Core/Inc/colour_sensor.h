#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

typedef enum Colour {
	RED = 0b00,
	BLUE = 0b01,
	CLEAR = 0b10,
	GREEN = 0b11
} Colour;

float getReading();
void setColour(Colour colour);

#endif
