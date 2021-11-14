#include <test.h>

#include <stdbool.h>

#include <colour_sensor.h>
#include <motor.h>
#include <main.h>
#include <servo.h>

void testColourSensor(UART_HandleTypeDef *huart6, TIM_HandleTypeDef *htim2) {
	Colour colour = getLeftColour(huart6);
	if (colour == RED) {
		openServo(htim2);
	} else if (colour == GREEN) {
		closeServo(htim2);
	} else if (colour == BLUE) {
		openServo(htim2);
		closeServo(htim2);
	}
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
