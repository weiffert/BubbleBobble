#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Projectile.h"

class Bubble : public Projectile
{
public:
	Bubble(sf::RenderWindow *, GameData *);
	~Bubble();
private:
	sf::RectangleShape bubble;
	sf::Texture bubbleTexture;
	bool containsEnemy;
};