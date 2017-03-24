#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();
	virtual void updateVelocity();
	virtual void levelEnd();
	virtual void levelStart();
	virtual void death();
	virtual void timeLimitPassed();
};

