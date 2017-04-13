#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
	name = "Projectile";
	window = nullptr;
	gameData = nullptr;
}


Projectile::Projectile(sf::RenderWindow *win, GameData *data)
{
	name = "Projectile";
	window = win;
	gameData = data;
}


Projectile::~Projectile()
{
}


void Projectile::collideWith()
{
	std::vector<GameObject*> data;
	//level
	data = gameData->getList(0);
	data.at(0)->collision(this);
}


void Projectile::collided(GameObject *other)
{
	std::string otherName = other->getName();
	//If it is a monster.
	if (!other->isFriendly())
	{
		death();
	}
}


void Projectile::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(4, temp);
}