#include <test.h>

#include <stdbool.h>

#include <colour_sensor.h>
#include <imu.h>
#include <motor.h>
#include <main.h>
#include <servo.h>

volatile Colour colourRight;
volatile Colour colourLeft;
RGB rgbRight;
volatile uint8_t redRight;
volatile uint8_t greenRight;
volatile uint8_t blueRight;
void testColourSensor() {
	getRightRGB(&rgbRight);
	redRight = rgbRight.red;
	greenRight = rgbRight.green;
	blueRight = rgbRight.blue;
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
