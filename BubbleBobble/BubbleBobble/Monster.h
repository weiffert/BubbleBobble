#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	~Monster();
	virtual void death();
	virtual void levelStart();
	virtual void distanceLimitPassed();

private:
	bool noLevelCollision;
};

