#pragma once
#include "Monster.h"
class Skel_Monsta :
	public Monster
{
public:
	Skel_Monsta();
	Skel_Monsta(sf::RenderWindow *, GameData *);
	~Skel_Monsta();
};

