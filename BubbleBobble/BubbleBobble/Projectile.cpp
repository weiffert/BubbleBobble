#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(4, temp);
}