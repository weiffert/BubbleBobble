#pragma once
#include "Monster.h"
class Invader :
	public Monster
{
public:
	Invader();
	Invader(sf::RenderWindow *, GameData *);
	~Invader();
};

