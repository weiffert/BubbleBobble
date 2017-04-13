#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	Monster();
	Monster(sf::RenderWindow *, GameData *);
	~Monster();
	void collideWith();
	void collided(GameObject *);
	void captured(GameObject *);
	void death();
	void levelStart();
	void levelPlay();
	void distanceLimitPassed();

protected:
	bool noLevelCollision;
	bool contained;
};

