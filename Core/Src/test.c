#include <test.h>

#include <stdbool.h>

#include <colour_sensor.h>
#include <imu.h>
#include <motor.h>
#include <main.h>
#include <servo.h>

void testColourSensor(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart6, TIM_HandleTypeDef *htim2) {
	Colour colourRight = getRightColour(huart1);
	Colour colourLeft = getLeftColour(huart6);
	if (colourLeft == RED) {
		openServo(htim2);
	} else if (colourLeft == GREEN) {
		closeServo(htim2);
	} else if (colourLeft == BLUE) {
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

void testImu(I2C_HandleTypeDef *hi2c2) {
	readGyro(hi2c2);
}
