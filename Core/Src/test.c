#include <test.h>

#include <stdbool.h>

#include <colour_sensor.h>
#include <motor.h>
#include <main.h>
#include <servo.h>

void testColourSensor(ADC_HandleTypeDef* hadc1) {
	static float colourVal;
	setColour(BLUE);
	colourVal = getReading(hadc1);
}

void testMotors() {
	moveMotors();
}

bool once = false;
void testServo() {
	if (!once) {
		servoInit();
		once = true;
	}

	moveServo();
}
