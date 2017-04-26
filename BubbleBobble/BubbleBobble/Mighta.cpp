#include "stdafx.h"
#include "Mighta.h"


Mighta::Mighta()
{
	name = "Mighta";
	window = nullptr;
	gameData = nullptr;
}


Mighta::Mighta(sf::RenderWindow *win, GameData *data)
{
	name = "Mighta";
	window = win;
	gameData = data;
	setTexture("../texture/Characters/mighta.png");
	flipTexture();
}


Mighta::~Mighta()
{
}
