#include "stdafx.h"
#include "Banebou.h"


Banebou::Banebou()
{
	name = "Banebou";
	window = nullptr;
	gameData = nullptr;
}


Banebou::Banebou(sf::RenderWindow *win, GameData *data)
{
	name = "Banebou";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/banebou.png");
	flipTexture();
}


Banebou::~Banebou()
{
}
