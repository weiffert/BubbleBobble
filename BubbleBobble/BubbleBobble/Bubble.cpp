#include "stdafx.h"
#include "Bubble.h"
#include <iostream>


Bubble::Bubble(sf::RenderWindow * win, GameData * dat, Player * source) : Projectile(win, dat)
{
	name = "Bubble";
	gameData = dat;
	window = win;
	containsEnemy = false;

	texture.loadFromFile("../textures/Projectile/bubble.png");
	rectangle.setTexture(&texture);
	sf::Vector2f playerPos = source->getRectangle().getPosition();
	rectangle.setPosition(playerPos.x, playerPos.y);
	rectangle.setFillColor(sf::Color::Green);
}


Bubble::~Bubble()
{
}