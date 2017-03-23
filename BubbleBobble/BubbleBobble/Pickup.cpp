#include "stdafx.h"
#include "Pickup.h"
#include "PointText.h"

//have an individualized sprite, point value, and in collided calls player.pickedUp()

Pickup::Pickup()
{
}


Pickup::~Pickup()
{
}

//pickup death

void Pickup::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(3, temp);
	
	temp = new PointText(this, 100, false);
	gameData->add(5, temp);
	//Add points to player total.
}