#include "stdafx.h"
#include "Invader.h"


Invader::Invader()
{
	name = "Invader";
	window = nullptr;
	gameData = nullptr;
}


Invader::Invader(sf::RenderWindow *win, GameData *data)
{
	name = "Invader";
	window = win;
	gameData = data;
}


Invader::~Invader()
{
}
