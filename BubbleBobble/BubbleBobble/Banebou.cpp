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
	name = "";
	window = win;
	gameData = data;
}


Banebou::~Banebou()
{
}
