#include "stdafx.h"
#include "Drunk.h"


Drunk::Drunk()
{
	name = "Drunk";
	window = nullptr;
	gameData = nullptr;
}


Drunk::Drunk(sf::RenderWindow *win, GameData *data)
{
	name = "Drunk";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/drunk.png");
	flipTexture();
}


Drunk::~Drunk()
{
}
