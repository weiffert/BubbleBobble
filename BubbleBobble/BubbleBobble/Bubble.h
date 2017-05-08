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
	void distanceLimitPassed();
	void collided(GameObject *);
	void pop();
	std::vector<bool> levelPathing(std::vector<int>, std::vector<int>);
private:
	GameObject * monsterContained;
};