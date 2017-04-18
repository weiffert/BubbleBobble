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
	//bool getUpMovement();
	//bool getLeftMovement();

protected:
	//virtual void path();
	bool noLevelCollision;
	bool contained;
	//bool upMovement;
	//bool leftMovement;
};

