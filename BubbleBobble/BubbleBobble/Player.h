#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(std::string, sf::RenderWindow *, GameData *);
	~Player();
	void update();
	void collideWith();
	void collided(GameObject *);
	void pickedUp(GameObject *);
	void levelEnd();
	void levelStart();
	void levelPlay();
	void levelTransition();
	void death();
	void timeLimitPassed();
};