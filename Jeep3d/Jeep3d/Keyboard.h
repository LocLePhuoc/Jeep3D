#pragma once
#include "Mesh.h"
enum Direction
{
	IDLE,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	TURN_LEFT_FORWARD,
	TURN_RIGHT_FORWARD,
	TURN_LEFT_BACKWARD,
	TURN_RIGHT_BACKWARD,
};

enum BasicKeyEvent {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_FORWARD,
	KEY_BACKWARD,
};

class Keyboard {
private:
	bool left;
	bool right;
	bool forward;
	bool backward;
	float forwardVelocity;
	float backwardVelocity;
	Direction currentDirection;
public:
	Keyboard() {
		left = right = forward = backward = false;
		currentDirection = IDLE;
		forwardVelocity = 0;
		backwardVelocity = 0;
	}

	Direction getDirection();
	void setVelocities(float forward, float backward);
	void onKeyEventDown(BasicKeyEvent event);
	void onKeyEventUp(BasicKeyEvent event);
};