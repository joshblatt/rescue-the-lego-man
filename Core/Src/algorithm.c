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

volatile Colour leftColour = NO_COLOUR;
volatile Colour rightColour = NO_COLOUR;

void movement(Colour stopColour) {
	// need to test if condition will break at any unintended time
	// need to test if params (left/right color, left/right slowed) carry over (pass as copy or pass with address thing)

	bool condition = true;
	bool turn = false;
	while (condition) {
		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn

		// TODO:
		// turn speedleft/right and regleft/right into one function
		//



		leftColour = getLeftColour();
		rightColour = getRightColour();

		// turning conditions
		if (leftColour == RED || rightColour == RED)	{
			// only stop motors if it hasnt started turn yet
			// room for error with this - not sure how fast it can switch from turning left to turning right or from turn to straight
			// valid option to stop after each micro-turn - initial implementation is to stop, turn a bit, stop, turn a bit until turn is complete
			// optimistic goal is to not stop after each micro-turn - turn, turn again, turn again, etc. until turn complete

			if (!turn) {
				stopMotors();
				speedLeftMotors();
				speedRightMotors();
				HAL_Delay(50);
			}
			if (leftColour == RED) {
				turnLeft();
				HAL_Delay(50);
			}
			else if (rightColour == RED) {
				turnRight();
				HAL_Delay(50);
			}
			turn = true;
		}
		// coming out of turn - reset motors to regular speed, change bool to false to signify that turn its not in turn
		else {
			if (turn) {
				regularLeftMotors();
				regularRightMotors();
				moveForwards();
				HAL_Delay(50);
				turn = false;
			}
		}

		if (stopColour == GREEN) condition = leftColour != stopColour || rightColour != stopColour;
		// was previously &&
		else condition = leftColour != stopColour || rightColour != stopColour;

	}
}

void pickup() {
	stopMotors();
	openServo();
	HAL_Delay(50);

	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(50);

	moveForwards();
	HAL_Delay(50);

	bool bothRed = false;
	// Follow line until both sensors see red
	while (!bothRed) {
		leftColour = getLeftColour();
		rightColour = getRightColour();

		if (leftColour == RED && rightColour != RED) {
			stopMotors();
			HAL_Delay(50);
			turnLeft();
			HAL_Delay(50);
		} else if (leftColour != RED && rightColour == RED) {
			stopMotors();
			HAL_Delay(50);
			turnRight();
			HAL_Delay(50);
		} else if (leftColour == RED && rightColour == RED) {
			bothRed = true;
		} else {
			stopMotors();
			HAL_Delay(50);
			moveForwards();
			HAL_Delay(50);
		}
	}
	// once they both see red, move forwards very slowly, close servo
	stopMotors();
	HAL_Delay(50);
	slowRightMotors();
	slowLeftMotors();
	HAL_Delay(50);
	moveForwards();
	HAL_Delay(500);
	stopMotors();
	HAL_Delay(50);
	closeServo();
	HAL_Delay(300);
}

void turnAround() {
	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(50);
	moveBackwards();
	HAL_Delay(1000);

	stopMotors();
	HAL_Delay(50);
	turnRight();

	while (getRightColour() != RED) {
		HAL_Delay(50);
	}
	while (getLeftColour() != RED) {
		HAL_Delay(50);
	}
	stopMotors();
	HAL_Delay(50);
}

void goHome(Colour stopColour) {
	// need to test if condition will break at any unintended time
	// need to test if params (left/right color, left/right slowed) carry over (pass as copy or pass with address thing)

	moveForwards();
	HAL_Delay(50);

	bool condition = true;
	bool turn = false;
	while (condition) {
		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn

		// TODO:
		// turn speed left/right and regleft/right into one function
		//



		leftColour = getLeftColour();
		rightColour = getRightColour();

		// turning conditions
		if ((leftColour == RED  && rightColour != RED ) || (rightColour == RED && leftColour != RED))	{
			// only stop motors if it hasnt started turn yet
			// room for error with this - not sure how fast it can switch from turning left to turning right or from turn to straight
			// valid option to stop after each micro-turn - initial implementation is to stop, turn a bit, stop, turn a bit until turn is complete
			// optimistic goal is to not stop after each micro-turn - turn, turn again, turn again, etc. until turn complete

			if (!turn) {
				stopMotors();
				speedLeftMotors();
				speedRightMotors();
				HAL_Delay(50);
			}
			if (leftColour == RED) {
				turnLeft();
				HAL_Delay(50);
			}
			else if (rightColour == RED) {
				turnRight();
				HAL_Delay(50);
			}
			turn = true;
		}
		// coming out of turn - reset motors to regular speed, change bool to false to signify that turn its not in turn
		else {
			if (turn) {
				regularLeftMotors();
				regularRightMotors();
				moveForwards();
				HAL_Delay(50);
				turn = false;
			}
		}
		// break when left = red && right = red
		condition = leftColour != stopColour || rightColour != stopColour;

	}
}

void searchAndRescue()	{
	// Move to pickup zone
	moveForwards();
	movement(BLUE);

	// Pickup Lego Man
	pickup();
	// Turn around
	turnAround();

	goHome(RED);
	stopMotors();
	HAL_Delay(50);
	openServo();
	HAL_Delay(300);
}

