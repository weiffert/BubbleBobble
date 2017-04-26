#include "stdafx.h"
#include "Monsta.h"


Monsta::Monsta()
{
	name = "Monsta";
	window = nullptr;
	gameData = nullptr;
}


Monsta::Monsta(sf::RenderWindow *win, GameData *data)
{
	name = "Monsta";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/monsta.png");
	flipTexture();
}


Monsta::~Monsta()
{
}
