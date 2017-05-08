#include "stdafx.h"
#include "Pulpul.h"


Pulpul::Pulpul()
{
	name = "Monster Pulpul";
	window = nullptr;
	gameData = nullptr;
}


Pulpul::Pulpul(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Pulpul";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/pulpul.png");
	flipTexture();
}


Pulpul::~Pulpul()
{
}
