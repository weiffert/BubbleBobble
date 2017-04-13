#include "stdafx.h"
#include "Zenchan.h"
#include <iostream>


Zenchan::Zenchan()
{
	name = "Zenchan";
	window = nullptr;
	gameData = nullptr;
}


Zenchan::Zenchan(sf::RenderWindow *win, GameData *data)
{
	name = "Zenchan";
	window = win;
	gameData = data;
}


Zenchan::~Zenchan()
{
}
