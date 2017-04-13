#pragma once
#include "GameObject.h"
class Pickup :
	public GameObject
{
public:
	Pickup();
	Pickup(sf::RenderWindow *, GameData *);
	~Pickup();
	void collideWith();
	void collided(GameObject *);
	void death();
};

