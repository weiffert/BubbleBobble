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
}


Monster::~Monster()
{
}

void Monster::collideWith()
{
	//projectiles
	std::vector<GameObject*> data = gameData->getList(4);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
}

void Monster::levelStart()
{
	setVelocity(0, 1);
}

void Monster::levelPlay()
{
	if (!noLevelCollision)
	{
		//any change.
		//check for collision.
		gameData->getList(0).at(0)->collision(this);
		//move.
		rectangle.move(velocity);
	}
	else
	{
		rectangle.move(velocity);
		distance();
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
	temp->initialize(window, gameData);
	gameData->add(5, temp);
}

void Monster::distanceLimitPassed()
{
	noLevelCollision = false;
	velocity.y = 0;
}