#include "stdafx.h"
#include "Bubble.h"


Bubble::Bubble(sf::RenderWindow * win, GameData * dat)
{
	name = "Bubble";
	gameData = dat;
	window = win;
	containsEnemy = false;

	bubbleTexture.loadFromFile("../textures/Projectile/bubble.png");
	bubble.setTexture(&bubbleTexture);
}


Bubble::~Bubble()
{
}