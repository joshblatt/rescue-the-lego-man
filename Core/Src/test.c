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
	//moveMotors();
	moveForwards();
	stopMotors();
	moveBackwards();
	stopMotors();
	turnRight();
	stopMotors();
	turnLeft();
	stopMotors();
}

void testServo(TIM_HandleTypeDef *htim2) {
	moveServo(htim2);
}
