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
RGB rgbLeft;

volatile uint8_t redRight;
volatile uint8_t greenRight;
volatile uint8_t blueRight;
volatile uint8_t redLeft;
volatile uint8_t greenLeft;
volatile uint8_t blueLeft;
void testColourSensor() {
	getRightRGB(&rgbRight);
	redRight = rgbRight.red;
	greenRight = rgbRight.green;
	blueRight = rgbRight.blue;

	getLeftRGB(&rgbLeft);
	redLeft = rgbLeft.red;
	greenLeft = rgbLeft.green;
	blueLeft = rgbLeft.blue;
}

void testMotors() {
	moveForwards();
	HAL_Delay(3000);
	stopMotors();
	HAL_Delay(3000);
	moveBackwards();
	HAL_Delay(3000);
	stopMotors();
	HAL_Delay(3000);
	turnRight();
	HAL_Delay(3000);
	stopMotors();
	HAL_Delay(3000);
	turnLeft();
	HAL_Delay(3000);
	stopMotors();
	HAL_Delay(3000);
}

void testServo() {
	moveServo();
}

void testImu() {
	readGyro();
}
