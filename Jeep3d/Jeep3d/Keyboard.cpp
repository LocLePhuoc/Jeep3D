#include "Keyboard.h"
#include <iostream>
using namespace std;

Direction Keyboard::getDirection() {
	if (left == true) {
		currentDirection = LEFT;
	}

	if (left == true && forwardVelocity > 0) {
		currentDirection = TURN_LEFT_FORWARD;
	}

	if (left == true && backwardVelocity > 0) {
		currentDirection = TURN_LEFT_BACKWARD;
	}

	if (right == true) {
		currentDirection = RIGHT;
	}

	if (right == true && forwardVelocity > 0) {
		currentDirection = TURN_RIGHT_FORWARD;
	}

	if (right == true && backwardVelocity > 0) {
		currentDirection = TURN_RIGHT_BACKWARD;
	}

	if (forward == true) {
		currentDirection = FORWARD;
	}

	if (backward == true) {
		currentDirection = BACKWARD;
	}

	if (left == true && forward == true) {
		currentDirection = TURN_LEFT_FORWARD;
	}

	if (left == true && backward == true) {
		currentDirection = TURN_LEFT_BACKWARD;
	}

	if (right == true && forward == true) {
		currentDirection = TURN_RIGHT_FORWARD;
	}

	if (right == true && backward == true) {
		currentDirection = TURN_RIGHT_BACKWARD;
	}

	if ((left == right && left != false) || (forward == backward && forward != false)) {
		currentDirection = IDLE;
	}
	if (left == false
		&& right == false
		&& forward == false
		&& backward == false) {
		currentDirection = IDLE;
	}
	return currentDirection;
}

void Keyboard::setVelocities(float forward, float backward) {
	forwardVelocity = forward;
	backwardVelocity = backward;
}

void Keyboard::onKeyEventDown(BasicKeyEvent event) {
	if (event == KEY_LEFT) left = true;
	if (event == KEY_RIGHT)right = true;
	if (event == KEY_FORWARD) forward = true;
	if (event == KEY_BACKWARD) backward = true;
}

void Keyboard::onKeyEventUp(BasicKeyEvent event) {
	if (event == KEY_LEFT) left = false;
	if (event == KEY_RIGHT) right = false;
	if (event == KEY_FORWARD) forward = false;
	if (event == KEY_BACKWARD) backward = false;
}
