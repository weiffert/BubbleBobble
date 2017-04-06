#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	~Monster();
	void collideWith();
	void collided(GameObject *);
	void captured(GameObject *);
	void death();
	void levelStart();
	void levelPlay();
	void distanceLimitPassed();

private:
	bool noLevelCollision;
	bool contained;
};

