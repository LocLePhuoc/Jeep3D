#include "Movement.h"
#include <chrono>
#include <iostream>
#define D2G 3.14159/180

using namespace std;
float Movement::getForwardVelocity() {
	return forwardVelocity;
}
float Movement::getBackwardVelocity() {
	return backwardVelocity;
}
void Movement::setDirection(Direction direction) {
	steeringAction = direction;
}

float Movement::getSteerAngleIncrement() {
	return steerAngleIncrement;
}
float Movement::getDistanceTraveled()
{
	return distanceTraveled;
}
Direction Movement::getCurrentAction() {
	return steeringAction;
}

void Movement::moveForward(float timeElapsed) {
	if (backwardVelocity > 0) {
		acceleration = - 200;
		moveBackward(timeElapsed);
	}
	else {
		backwardVelocity = 0;
		float distanceTraveled = forwardVelocity * timeElapsed;
		forwardVelocity = (forwardVelocity >= 1001) ? 1000 : forwardVelocity + acceleration * timeElapsed;
		currentX += forwardVector.x * distanceTraveled / forwardVector.size();
		currentZ += forwardVector.z * distanceTraveled / forwardVector.size();
	}
}

void Movement::moveBackward(float timeElapsed) {
	if (forwardVelocity > 0) {
		acceleration = -400;
		moveForward(timeElapsed);
	}
	else {
		forwardVelocity = 0;
		float distanceTraveled = backwardVelocity * timeElapsed;
		backwardVelocity = (backwardVelocity >= 501) ? 500 : backwardVelocity + acceleration * timeElapsed;
		currentX -= forwardVector.x * distanceTraveled / forwardVector.size();
		currentZ -= forwardVector.z * distanceTraveled / forwardVector.size();
	}
}

void Movement::turnLeftForWard(float timeElapsed) {
	forwardVector = Vector3(forwardVector.x * cos(steerAngleIncrement * D2G) + sin(steerAngleIncrement * D2G) * forwardVector.z,0,forwardVector.x * -sin(steerAngleIncrement * D2G) + cos(steerAngleIncrement * D2G) * forwardVector.z);
	distanceTraveled = forwardVelocity * timeElapsed;
	currentX += forwardVector.x * distanceTraveled / forwardVector.size();
	currentZ += forwardVector.z * distanceTraveled / forwardVector.size();
}

void Movement::turnRightForWard(float timeElapsed) {
	forwardVector = Vector3(forwardVector.x * cos(-steerAngleIncrement * D2G) + sin(-steerAngleIncrement * D2G) * forwardVector.z, 0, forwardVector.x * -sin(-steerAngleIncrement * D2G) + cos(-steerAngleIncrement * D2G) * forwardVector.z);
	distanceTraveled = forwardVelocity * timeElapsed;
	currentX += forwardVector.x * distanceTraveled / forwardVector.size();
	currentZ += forwardVector.z * distanceTraveled / forwardVector.size();
}

void Movement::turnLeftBackWard(float timeElapsed) {
	forwardVector = Vector3(forwardVector.x * cos(-steerAngleIncrement * D2G) + sin(-steerAngleIncrement * D2G) * forwardVector.z, 0, forwardVector.x * -sin(-steerAngleIncrement * D2G) + cos(-steerAngleIncrement * D2G) * forwardVector.z);
	distanceTraveled = backwardVelocity * timeElapsed;
	currentX -= forwardVector.x * distanceTraveled / forwardVector.size();
	currentZ -= forwardVector.z * distanceTraveled / forwardVector.size();
}

void Movement::turnRightBackWard(float timeElapsed) {
	forwardVector = Vector3(forwardVector.x * cos(steerAngleIncrement * D2G) + sin(steerAngleIncrement * D2G) * forwardVector.z, 0, forwardVector.x * -sin(steerAngleIncrement * D2G) + cos(steerAngleIncrement * D2G) * forwardVector.z);
	distanceTraveled = backwardVelocity * timeElapsed;
	currentX -= forwardVector.x * distanceTraveled / forwardVector.size();
	currentZ -= forwardVector.z * distanceTraveled / forwardVector.size();
}

float Movement::move() {
	//no action has been initiated
	float timeElapsed = 0;
	if (previousTime == 0) {
		previousTime = glutGet(GLUT_ELAPSED_TIME);
	}
	else {
		timeElapsed = glutGet(GLUT_ELAPSED_TIME) - previousTime;
		previousTime += timeElapsed;
	}
	if (timeElapsed > 0) {
		if (getCurrentAction() == FORWARD) {
			acceleration = 100;
			moveForward(timeElapsed / 1000);
		} 
		if (getCurrentAction() == BACKWARD) {
			acceleration = 100;
			moveBackward(timeElapsed / 1000);
		}
		if (getCurrentAction() == TURN_LEFT_FORWARD) {
			turnLeftForWard(timeElapsed / 1000);
		}
		if (getCurrentAction() == TURN_RIGHT_FORWARD) {
			turnRightForWard(timeElapsed / 1000);
		}
		if (getCurrentAction() == TURN_LEFT_BACKWARD) {
			turnLeftBackWard(timeElapsed / 1000);
		}
		if (getCurrentAction() == TURN_RIGHT_BACKWARD) {
			turnRightBackWard(timeElapsed / 1000);
		}
		if (getCurrentAction() == IDLE) {
			if (forwardVelocity > 0) { //car is moving forward
				acceleration = -100;
				moveForward(timeElapsed / 1000);
			}

			if (backwardVelocity > 0) {
				acceleration = -100;
				moveBackward(timeElapsed / 1000);
			}
		}
	}
	return timeElapsed;
}