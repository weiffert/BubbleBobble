#pragma once
#include "Monster.h"
class Drunk :
	public Monster
{
public:
	Drunk();
	Drunk(sf::RenderWindow *, GameData *);
	~Drunk();
};

