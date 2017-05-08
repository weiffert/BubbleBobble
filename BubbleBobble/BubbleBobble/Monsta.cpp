#include "stdafx.h"
#include "Monsta.h"


Monsta::Monsta()
{
	name = "Monster Monsta";
	window = nullptr;
	gameData = nullptr;
}


Monsta::Monsta(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Monsta";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/monsta.png");
	flipTexture();
}


Monsta::~Monsta()
{
}
