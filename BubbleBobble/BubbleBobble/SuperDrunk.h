#pragma once
#include "Monster.h"
class SuperDrunk :
	public Monster
{
public:
	SuperDrunk();
	SuperDrunk(sf::RenderWindow *, GameData *);
	~SuperDrunk();
};

