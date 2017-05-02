#include "stdafx.h"
#include "Bubble.h"
#include <iostream>


Bubble::Bubble(sf::RenderWindow * win, GameData * dat, Player * player) : Projectile(win, dat)
{
	name = "Bubble";
	gameData = dat;
	window = win;
	monsterContained = nullptr;

	setTexture("../textures/Projectile/bubble.png");
	sf::Vector2f playerPos = player->getRectangle().getPosition();
	rectangle.setPosition(playerPos.x, playerPos.y);
	setVelocity(player->getDirection() * SCREEN_MULTIPLIER * 1.25, 0);
	startPedometer();
}


Bubble::~Bubble()
{
}