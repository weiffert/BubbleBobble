#include "stdafx.h"
#include "Zenchan.h"
#include <iostream>


Zenchan::Zenchan()
{
	name = "Zenchan";
	window = nullptr;
	gameData = nullptr;
	setTexture("../textures/Characters/Zenchan.png");
}


Zenchan::Zenchan(sf::RenderWindow *win, GameData *data)
{
	name = "Zenchan";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/Zenchan.png");
	flipTexture();
}


Zenchan::~Zenchan()
{
}