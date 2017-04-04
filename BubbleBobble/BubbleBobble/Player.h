#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(std::string);
	~Player();
	virtual void collideWith();
	virtual void updateVelocity();
	virtual void levelEnd();
	virtual void levelStart();
	virtual void death();
	virtual void timeLimitPassed();
	virtual void moveLeft(float);
	virtual void moveRight(float);
	virtual void jump();
	virtual void stopXMovement();
	virtual void stopYMovement();
};

