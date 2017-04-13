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
}


Monsta::~Monsta()
{
}
