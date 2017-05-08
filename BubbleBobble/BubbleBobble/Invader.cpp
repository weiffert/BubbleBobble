#include "stdafx.h"
#include "Invader.h"


Invader::Invader()
{
	name = "Monster Invader";
	window = nullptr;
	gameData = nullptr;
}


Invader::Invader(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Invader";
	window = win;
	gameData = data;
	setTexture("../texture/Character/invader.png");
	flipTexture();
}


Invader::~Invader()
{
}
