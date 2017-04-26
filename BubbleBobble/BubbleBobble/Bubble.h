#pragma once
#include "Projectile.h"
#include <SFML\Graphics.hpp>
#include "GameData.h"

class Bubble :
	public Projectile
{
public:
	Bubble();
	Bubble(sf::RenderWindow *, GameData *);
	~Bubble();
};