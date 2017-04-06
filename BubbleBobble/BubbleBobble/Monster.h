#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	~Monster();
	void collideWith();
	void death();
	void levelStart();
	void levelPlay();
	void distanceLimitPassed();

private:
	bool noLevelCollision;
};

