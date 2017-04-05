#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	~Monster();
	void collideWith();
	virtual void death();
	virtual void updateVelocity();
	void distanceLimitPassed();

private:
	bool noLevelCollision;
};

