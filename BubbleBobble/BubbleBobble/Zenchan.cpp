#include "stdafx.h"
#include "Zenchan.h"
#include <iostream>


Zenchan::Zenchan()
{
	name = "Monster Zenchan";
	window = nullptr;
	gameData = nullptr;
	setTexture("../textures/Characters/Zenchan.png");
}


Zenchan::Zenchan(sf::RenderWindow *win, GameData *data)
{
	name = "Monster Zenchan";

	std::cout << "Name: " << name.substr(8);

	window = win;
	gameData = data;
	setTexture("../textures/Characters/Zenchan.png");
	flipTexture();
}


Zenchan::~Zenchan()
{
}