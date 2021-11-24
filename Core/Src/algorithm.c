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

// TODO: 11/24
// clean up code - make functions to handle repeatitive actions
	// turn speedleft/right and regleft/right into one function
	// remove unused functions
// test blue code - should adjust fine but will need to test
// testing for green code


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

	// condition - break condition for while loop; dependent on colour, evaluated at end of each iteration
	bool condition = true;
	// turn - boolean to track whether robot is in a turn or not, adjusts speed of motors accordingly - prevents constant calls to moveForwards which would be expensive
	bool turn = false;

	moveForwards();
	HAL_delay(50);

	while (condition) {
		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn

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

		// was previously ||
		if (stopColour == GREEN) condition = leftColour != stopColour && rightColour != stopColour;

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
	// at this point - legoman has been picked up

}


// called when green is first seen
// inch up a bit, turn left, drop off
// move back a bit (maybe dont need to)
// turn right, and finish
void dropoff() {
	stopMotors();
	HAL_Delay(50);

	slowRightMotors();
	slowLeftMotors();
	HAL_Delay(50);

	moveForwards();
	// timing will be adjusted to let robot get to midpoint of green zone
	HAL_Delay(100);
	stopMotors();
	HAL_Delay(50);

	// using assumption that dropoff will happen at FIRST dropoff one which is detected by the LEFT SENSOR which sees GREEN
	turnLeft();

	HAL_Delay(100);
	stopMotors();
	HAL_Delay(50);

	openServo();
	HAL_Delay(300);
	// at this point - legoman has been dropped off
}

void turnAround(int backwardsTime) {
	// backwardsTime is time that robot will move backwards (in ms)
	// different cases will need different times
		// moving back from blue is longer than moving back from green
	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(50);
	moveBackwards();
	HAL_Delay(backwardsTime);

	stopMotors();
	HAL_Delay(50);

	// begin right rotation to turn 180
	turnRight();

	// turn until right sensor hits red
	while (getRightColour() != RED) {
		HAL_Delay(50);
	}
	// now turn until left sensor hits red
	while (getLeftColour() != RED) {
		HAL_Delay(50);
	}
	stopMotors();
	HAL_Delay(50);
	// at this point - robot has turned around and can begin line following
}


// identical to movement - commented for now just to be safe but will remove when movement(RED) is tested and good to go

//void goHome(Colour stopColour) {
//	// need to test if condition will break at any unintended time
//	// need to test if params (left/right color, left/right slowed) carry over (pass as copy or pass with address thing)
//
//	moveForwards();
//	HAL_Delay(50);
//
//	bool condition = true;
//	bool turn = false;
//	while (condition) {
//		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
//		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn
//
//		// TODO:
//		// turn speed left/right and regleft/right into one function
//		//
//
//
//
//		leftColour = getLeftColour();
//		rightColour = getRightColour();
//
//		// turning conditions
//		if ((leftColour == RED  && rightColour != RED ) || (rightColour == RED && leftColour != RED))	{
//			// only stop motors if it hasnt started turn yet
//			// room for error with this - not sure how fast it can switch from turning left to turning right or from turn to straight
//			// valid option to stop after each micro-turn - initial implementation is to stop, turn a bit, stop, turn a bit until turn is complete
//			// optimistic goal is to not stop after each micro-turn - turn, turn again, turn again, etc. until turn complete
//
//			if (!turn) {
//				stopMotors();
//				speedLeftMotors();
//				speedRightMotors();
//				HAL_Delay(50);
//			}
//			if (leftColour == RED) {
//				turnLeft();
//				HAL_Delay(50);
//			}
//			else if (rightColour == RED) {
//				turnRight();
//				HAL_Delay(50);
//			}
//			turn = true;
//		}
//		// coming out of turn - reset motors to regular speed, change bool to false to signify that turn its not in turn
//		else {
//			if (turn) {
//				regularLeftMotors();
//				regularRightMotors();
//				moveForwards();
//				HAL_Delay(50);
//				turn = false;
//			}
//		}
//		// break when left = red && right = red
//		condition = leftColour != stopColour || rightColour != stopColour;
//
//	}
//}

void searchAndRescue()	{
	// PHASE 1
	// Move to pickup zone
	movement(BLUE);
	// Pickup Lego Man
	pickup();
	// Turn around
	turnAround(1000);

	// PHASE 2
	// Move to green zone
	movement(GREEN);
	// Drop off robot
	dropoff();
	// Turn around
	turnAround(250);

	// PHASE 3
	// Move to home
	movement(RED);
	// Stop at start
	stopMotors();
	HAL_Delay(50);
//	openServo();
//	HAL_Delay(300);
}

