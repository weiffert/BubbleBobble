#include "stdafx.h"
#include "Hidegons.h"


Hidegons::Hidegons()
{
	name = "Hidegons";
	window = nullptr;
	gameData = nullptr;
}


Hidegons::Hidegons(sf::RenderWindow *win, GameData *data)
{
	name = "Hidegons";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/hidegon.png");
	flipTexture();
}


Hidegons::~Hidegons()
{
}
