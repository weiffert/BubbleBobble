#include "stdafx.h"
#include "Monster.h"
#include "Pickup.h"


Monster::Monster()
{
}


Monster::~Monster()
{
}


void Monster::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(2, temp);

	//pickup creation
	//something like...
	temp = new Pickup();
	gameData->add(5, temp);
}