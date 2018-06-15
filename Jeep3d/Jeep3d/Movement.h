#pragma once
#include "Keyboard.h"

class Movement {
private:
	Direction steeringAction;
	float forwardVelocity;
	float backwardVelocity;
	float deltaTime;
	float acceleration;
	float steerAngleIncrement;
	float distanceTraveled;
	Vector3 forwardVector;

	//time to monitor the movement
	float previousTime;
public:
	float currentX;
	float currentZ;
	float jeepSteerAngle;
	Movement() {
		forwardVelocity = 0;
		backwardVelocity = 0;
		deltaTime = 0.1; //in seconds
		acceleration = 0;
		steeringAction = IDLE;
		currentX = 0;
		currentZ = 0;
		forwardVector = Vector3(1, 0, 0);
		jeepSteerAngle = 0;
		distanceTraveled = 0;
		steerAngleIncrement = 5;
		previousTime = 0;
	}
	float getForwardVelocity();
	float getBackwardVelocity();
	float getSteerAngleIncrement();
	float getDistanceTraveled();
	Direction getCurrentAction();
	void setDirection(Direction direction);
	void moveForward(float timeElapsed); 
	void moveBackward(float timeElapsed);
	void turnLeftForWard(float timeElapsed);
	void turnRightForWard(float timeElapsed);
	void turnLeftBackWard(float timeElapsed);
	void turnRightBackWard(float timeElapsed);
	float move();
};