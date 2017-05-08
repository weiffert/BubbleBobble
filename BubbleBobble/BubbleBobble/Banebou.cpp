#include "stdafx.h"
#include "Banebou.h"


Banebou::Banebou()
{
	name = "Monster Banebou";
	window = nullptr;
	gameData = nullptr;
}


Banebou::Banebou(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Banebou";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/banebou.png");
	flipTexture();
}


Banebou::~Banebou()
{
}
