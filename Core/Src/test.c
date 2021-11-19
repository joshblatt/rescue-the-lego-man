#include <test.h>

#include <stdbool.h>

#include <colour_sensor.h>
#include <imu.h>
#include <motor.h>
#include <main.h>
#include <servo.h>

volatile Colour colourRight;
volatile Colour colourLeft;
void testColourSensor() {
	colourRight = getRightColour();
	colourLeft = getLeftColour();
//	if (colourLeft == RED) {
//		openServo(htim2);
//	} else if (colourLeft == GREEN) {
//		closeServo(htim2);
//	} else if (colourLeft == BLUE) {
//		openServo(htim2);
//		closeServo(htim2);
//	}
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

void testServo() {
	moveServo();
}

void testImu(I2C_HandleTypeDef *hi2c2) {
	readGyro(hi2c2);
}
