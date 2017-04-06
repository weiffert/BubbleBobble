#pragma once
#include "GameObject.h"
class Pickup :
	public GameObject
{
public:
	Pickup();
	~Pickup();
	void collideWith();
	void collided(GameObject *);
	void death();
};

