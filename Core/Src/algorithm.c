#include <algorithm.h>

#include <motor.h>
#include <colour_sensor.h>
#include <stdbool.h>
#include <main.h>
#include <servo.h>

// written by Fayyad Reza
// C syntax might be weird at first, needs to be touched up


// Robot algorithm can be described into 3 movement phases, which unique processes at the end of each

// 1st Movement Phase: Search and Pickup
// Robot moves until it finds the blue danger zone
// Once blue zone is found, initiate pickup sequence
// Move forward a pre-determined (hardcoded) distance, activate servo and secure Lego Man, rotate 180 and move back to start of blue zone

// 2nd Movement Phase: Rescue and Dropoff
// Robot moves until it finds a green safe zone
// Once green zone is found, initiate dropoff sequence
// ---- NOT SURE YET ---
// Move forward a bit (get parallel to midpoint of green safe zone), turn 90 degrees into the safe zone, activate servo and drop Lego man, rotate back 90 degrees

// 3rd Movement Phase: Return to home
// Robot moves until it finds red perpendicular line (double red)
// Stop motors at red

void init(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim3, TIM_HandleTypeDef *htim2, TIM_HandleTypeDef *htim4) {
	  initMotors(htim1, htim3);
	  initServo(htim2);
	  initColourSensors(htim4);
}

void movement(Colour stopColour, Colour leftColour, Colour rightColour, bool leftSlowed, bool rightSlowed) 	{
	// need to test if condition will break at any unintended time
	// need to test if params (left/right color, left/right slowed) carry over (pass as copy or pass with address thing)

	bool condition = true;
	while (condition) {
		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn

		leftColour = getLeftColour();
		rightColour = getRightColour();

		if (leftColour == RED || rightColour == RED)	{
			if (leftColour == RED) {
				stopMotors();
				HAL_Delay(200);
				turnLeft();
				HAL_Delay(200);
//				while (getLeftColour() == RED) {
//					HAL_Delay(5);
//				}
				stopMotors();
				HAL_Delay(200);
				//slowLeftMotors();
				leftSlowed = true;
			}
			else if (rightColour == RED) {
				stopMotors();
				HAL_Delay(200);
				turnRight();
				HAL_Delay(200);
//				while (getRightColour() == RED) {
//					HAL_Delay(5);
//				}
				stopMotors();
				HAL_Delay(200);
				//slowRightMotors();
				rightSlowed = true;
			}
		}
		else {
			if (leftSlowed == true)	{
				leftSlowed = false;
				moveForwards();
				HAL_Delay(150);
			}
			if (rightSlowed == true)	{
				rightSlowed = false;
				moveForwards();
				HAL_Delay(150);
			}
		}

		if (stopColour == GREEN) condition = leftColour != stopColour || rightColour != stopColour;
		else condition = leftColour != stopColour && rightColour != stopColour;

	}
}

volatile Colour leftColour = NO_COLOUR;
volatile Colour rightColour = NO_COLOUR;

void searchAndRescue()	{
	// init()
	// need to have init function somewhere - will call initMotors(), initColorSensor(), initIMU(), initServo() -- essentially just initialize everything necessary


	// bool might be done wrong
	bool leftSlowed = false;
	bool rightSlowed = false;

	// move to blue danger zone
//	moveLeftMotors();
//	HAL_Delay(50);
//	speedLeftMotors();
//	HAL_Delay(3000);
//	stopMotors();
//	HAL_Delay(1000);
//	moveRightMotors();
//	HAL_Delay(50);
//	speedRightMotors();
//	HAL_Delay(3000);
//	stopMotors();

	moveForwards();
	movement(BLUE, leftColour, rightColour, leftSlowed, rightSlowed);

	stopMotors();
	openServo();
//
//	// NOT CORRECT - NEED TO MOVE BASED ON DISTANCE, RIGHT NOW DOING WITH ARBITRARY DELAY
//	moveForwards();
//	HAL_Delay(1680); // 10cm at 7cm/s at 85% speed => 1680~ms ---- might need to remove delay in moveForwards function;
//	stopMotors();
//	closeServo();
//
//	// ROTATE 180 - USED TURN RIGHT FOR NOW BUT WILL CHANGE WITH IMU
//	turnRight();
//	HAL_Delay(1000); // turnRight has 1000ms delay, which is approx 90 degrees - add another 1000ms delay to finish 180 rotate
//	stopMotors();

//	// move to green safe zone
//	// since its on the side, both colour sensors wont pick it up. once one of them reads green, we are at a safe zone and can initiate drop off
//	// TODO: put this into function - have BLUE/RED as params
//	moveForwards();
//	movement(GREEN, leftColour, rightColour, leftSlowed, rightSlowed);
//	stopMotors();
//
//	// NOT CORRECT - NEED TO MOVE BASED ON DISTANCE, RIGHT NOW DOING WITH ARBITRARY DELAY
//	moveForwards();
//	HAL_Delay(1500); // 9cm at 7cm/s at 85% speed ==> ~1500ms
//	stopMotors();
//
//	// ROTATE 90 IN SPECIFIC DIRECTION - USED TURN RIGHT FOR NOW BUT WILL CHANGE WITH IMU - turn left/right doesnt give 90 rn so have to change when IMU updated
//	if (leftColour == GREEN) turnLeft();
//	else turnRight();
//	stopMotors();
//	openServo();
//
//	// reverse turn in opposite direction to get back to red line (starting position when green initially found)
//	if (leftColour == GREEN) turnRight();
//	else turnLeft(); // left turn might be a bit buggier due to awkward wheel
//	stopMotors();
//
//	// move to home
//	moveForwards();
//	movement(RED, leftColour, rightColour, leftSlowed, rightSlowed);
//	stopMotors();
}

