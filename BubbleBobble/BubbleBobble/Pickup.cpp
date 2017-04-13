#include "stdafx.h"
#include "Pickup.h"
#include "PointText.h"

//have an individualized sprite, point value, and in collided calls player.pickedUp()

Pickup::Pickup()
{
	name = "Pickup";
	window = nullptr;
	gameData = nullptr;
}


Pickup::Pickup(sf::RenderWindow *win, GameData *data)
{
	name = "Pickup";
	window = win;
	gameData = data;
}


Pickup::~Pickup()
{
}


void Pickup::collideWith()
{
	std::vector<GameObject*> data;
	//level
	data = gameData->getList(0);
	data.at(0)->collision(this);
}


void Pickup::collided(GameObject *other)
{
	std::string otherName = other->getName();
	if (otherName.find("Player"))
		death();
}


void Pickup::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(3, temp);
	
	temp = new PointText(window, gameData, this, 100, false);
	gameData->add(5, temp);
	//Add points to player total.
}