#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Projectile.h"
#include "Player.h"

class Bubble : public Projectile
{
public:
	Bubble(sf::RenderWindow *, GameData *, Player *);
	~Bubble();
	void bubbleUp();
private:
	GameObject * monsterContained;
};