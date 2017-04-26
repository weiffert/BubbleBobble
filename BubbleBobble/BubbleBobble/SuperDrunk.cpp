#include "stdafx.h"
#include "SuperDrunk.h"


SuperDrunk::SuperDrunk()
{
	name = "SuperDrunk";
	window = nullptr;
	gameData = nullptr;
}


SuperDrunk::SuperDrunk(sf::RenderWindow *win, GameData *data)
{
	name = "SuperDrunk";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/superDrunk.png");
	flipTexture();
}


SuperDrunk::~SuperDrunk()
{
}
