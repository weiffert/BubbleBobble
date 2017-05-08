#include "stdafx.h"
#include "Drunk.h"


Drunk::Drunk()
{
	name = "Monster Drunk";
	window = nullptr;
	gameData = nullptr;
}


Drunk::Drunk(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Drunk";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/drunk.png");
	flipTexture();
}


Drunk::~Drunk()
{
}
