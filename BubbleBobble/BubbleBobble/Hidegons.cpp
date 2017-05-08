#include "stdafx.h"
#include "Hidegons.h"


Hidegons::Hidegons()
{
	name = "Monster Hidegons";
	window = nullptr;
	gameData = nullptr;
}


Hidegons::Hidegons(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Hidegons";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/hidegon.png");
	flipTexture();
}


Hidegons::~Hidegons()
{
}
