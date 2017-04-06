#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(std::string);
	~Player();
	void collideWith();
	void collided(GameObject *);
	void pickedUp(GameObject *);
	void levelEnd();
	void levelStart();
	void levelPlay();
	void levelTransition();
	void death();
	void timeLimitPassed();
	void moveLeft();
	void moveRight();
	void stopHorizontalVelocity();
	void jump();
	void stopXMovement();
	void stopYMovement();
	int getDirection();
private: 
	int direction;
};

