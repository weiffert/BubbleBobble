#pragma once
#include "GameObject.h"

/*
This is for bubbles and enemy projectiles. 
Has collisons with level, player, and enemy if friendly.
*/

class Projectile :
	public GameObject
{
public:
	Projectile();
	Projectile(sf::RenderWindow *, GameData *);
	~Projectile();
	void collideWith();
	void collided(GameObject *);
	void death();
	void render();
};