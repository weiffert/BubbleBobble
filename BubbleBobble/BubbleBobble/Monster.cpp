#include "stdafx.h"
#include "Monster.h"
#include "Pickup.h"
#include <iostream>


Monster::Monster()
{
	rectangle.setSize(sf::Vector2f(16, 16));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(500, 100);
	noLevelCollision = true;
	setVelocity(0, 1);
}


Monster::~Monster()
{
	std::cout << "Deconstructing Monster" << std::endl;
}

void Monster::collideWith()
{
	//projectiles
	std::vector<GameObject*> data = gameData->getList(4);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
}

void Monster::updateVelocity()
{
	if (!noLevelCollision)
	{
		//any change.
		//check for collision.
		gameData->getList(0).at(0)->collision(this);
		//move.
		rectangle.move(velocity);
	}
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

void Monster::distanceLimitPassed()
{
	noLevelCollision = false;
}