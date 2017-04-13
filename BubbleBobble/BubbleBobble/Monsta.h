#pragma once
#include "Monster.h"
class Monsta :
	public Monster
{
public:
	Monsta();
	Monsta(sf::RenderWindow *, GameData *);
	~Monsta();
};

