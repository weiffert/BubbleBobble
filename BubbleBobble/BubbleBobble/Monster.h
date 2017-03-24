#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	~Monster();
	virtual void collideWith();
	virtual void death();
	virtual void updateVelocity();
	virtual void distanceLimitPassed();

private:
	bool noLevelCollision;
};

