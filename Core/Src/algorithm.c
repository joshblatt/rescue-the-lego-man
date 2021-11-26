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

	rightColour = getRightColour();
	leftColour = getLeftColour();
	HAL_Delay(10);
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
				HAL_Delay(40);
			}
			if (leftColour == RED) {
				turnLeft();
				HAL_Delay(40);
			}
			else if (rightColour == RED) {
				turnRight();
				HAL_Delay(40);
			}
			turn = true;
		}
		// coming out of turn - reset motors to regular speed, change bool to false to signify that turn its not in turn
		else {
			if (turn) {
				regularLeftMotors();
				regularRightMotors();
				moveForwards();
				HAL_Delay(40);
				turn = false;
			}
		}

		if (stopColour == GREEN) condition = rightColour != stopColour;
		else condition = leftColour != stopColour || rightColour != stopColour;

	}
}

void pickup() {
	stopMotors();
	startServo();
	HAL_Delay(50);
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
			HAL_Delay(40);
		} else if (leftColour != RED && rightColour == RED) {
			stopMotors();
			HAL_Delay(50);
			turnRight();
			HAL_Delay(40);
		} else if (leftColour == RED && rightColour == RED) {
			bothRed = true;
		} else {
			stopMotors();
			HAL_Delay(50);
			moveForwards();
			HAL_Delay(40);
		}
	}
	// once they both see red, move forwards very slowly, close servo
	stopMotors();
	HAL_Delay(50);
	slowRightMotors();//slow
	slowLeftMotors();//slow
	HAL_Delay(50);
	moveForwards();
	HAL_Delay(500);
	stopMotors();
	HAL_Delay(50);
	closeServo();
	HAL_Delay(300);
	stopServo();
	HAL_Delay(50);
}

void turnAround() {
	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(50);
	moveBackwards();
	HAL_Delay(600);

	stopMotors();
	HAL_Delay(50);
	speedRightMotors();
	speedLeftMotors();
	HAL_Delay(50);
	turnRight();
	HAL_Delay(50);

	rightColour = getRightColour();
	leftColour = getLeftColour();
	HAL_Delay(50);
//	rightColour = getRightColour();
//	leftColour = getLeftColour();
//	HAL_Delay(50);

	while (rightColour != RED) {
		HAL_Delay(40);
		rightColour = getRightColour();

	}
	leftColour = getLeftColour();
	while (leftColour != RED) {
		HAL_Delay(40);
		leftColour = getLeftColour();
	}
	stopMotors();
	HAL_Delay(50);
	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(40);
}

// called when green is first seen
// inch up a bit, turn left, drop off
// move back a bit (maybe dont need to)
// turn right, and finish
void dropoff() {
	stopMotors();
	HAL_Delay(50);

//	slowRightMotors();
//	slowLeftMotors();
//	HAL_Delay(50);
//
//	moveForwards();
//	// timing will be adjusted to let robot get to midpoint of green zone
//	HAL_Delay(50);
//	stopMotors();
//	HAL_Delay(50);

	speedRightMotors();
	speedLeftMotors();
	HAL_Delay(50);

	// using assumption that dropoff will happen at FIRST dropoff one which is detected by the LEFT SENSOR which sees GREEN
	turnRight();

	HAL_Delay(450);
	stopMotors();
	HAL_Delay(50);

	regularRightMotors();
	regularLeftMotors();
	HAL_Delay(50);
	moveForwards();
	HAL_Delay(400);
	stopMotors();
	HAL_Delay(50);

	startServo();
	HAL_Delay(50);
	openServo();
	HAL_Delay(300);
	stopServo();
	HAL_Delay(50);
	// at this point - legoman has been dropped off

	moveBackwards();
	HAL_Delay(600);

	stopMotors();
	HAL_Delay(50);

	speedRightMotors();
	speedLeftMotors();
	HAL_Delay(50);

	turnLeft();
	HAL_Delay(20);
	rightColour = getRightColour();
	HAL_Delay(10);
	while (rightColour != RED) {
		HAL_Delay(20);
		rightColour = getRightColour();
	}

	stopMotors();
	HAL_Delay(50);
}

void goHome(Colour stopColour) {
	// need to test if condition will break at any unintended time
	// need to test if params (left/right color, left/right slowed) carry over (pass as copy or pass with address thing)

	bool condition = true;
	bool turn = true;
	rightColour = getRightColour();
	leftColour = getLeftColour();
	HAL_Delay(50);
	while (condition) {
		// possible optimizing - can check motor speed directly -- can get rid of leftslowed/rightslowed and just check the values direct to see if slowed
		// code currently slows motor down if it begins to turn (in that direction), and speeds it back up when it is out of the turn

		// TODO:
		// turn speedleft/right and regleft/right into one function
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

		if (stopColour == GREEN) condition = leftColour != stopColour || rightColour != stopColour;
		else condition = leftColour != stopColour || rightColour != stopColour;

	}
}

void searchAndRescue()	{
	// init()
	// need to have init function somewhere - will call initMotors(), initColorSensor(), initIMU(), initServo() -- essentially just initialize everything necessary


	// bool might be done wrong

	// move to blue danger zone
//	while(true) {
//		leftColour = getLeftColour();
//		rightColour = getRightColour();
//	}


	moveForwards();
	movement(BLUE);

	pickup();
	turnAround();

	movement(GREEN);
	dropoff();

//	moveForwards();
//	HAL_Delay(50);
	goHome(RED);
	stopMotors();
	startServo();
	closeServo();
	HAL_Delay(300);

	// move until both see red
	//


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
//	movement(GREEN);
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
//	movement(RED);
//	stopMotors();
}

