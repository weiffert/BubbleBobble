#include "stdafx.h"
#include "Pulpul.h"


Pulpul::Pulpul()
{
	name = "Pulpul";
	window = nullptr;
	gameData = nullptr;
}


Pulpul::Pulpul(sf::RenderWindow *win, GameData *data)
{
	name = "Pulpul";
	window = win;
	gameData = data;
}


Pulpul::~Pulpul()
{
}
