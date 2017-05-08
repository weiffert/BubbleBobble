#include "stdafx.h"
#include "Mighta.h"


Mighta::Mighta()
{
	name = "Monster Mighta";
	window = nullptr;
	gameData = nullptr;
}


Mighta::Mighta(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Mighta";
	window = win;
	gameData = data;
	setTexture("../texture/Characters/mighta.png");
	flipTexture();
}


Mighta::~Mighta()
{
}
