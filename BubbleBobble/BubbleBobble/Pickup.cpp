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
	
	GameObject *temp = new PointText(/*value*/ "100", this);
	gameData->add(5, temp);
}
//Add points to player total.
//make new PointText object.
//Add to vector of objects. 5th column.