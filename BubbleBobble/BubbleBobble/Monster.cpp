#include "stdafx.h"
#include "Monster.h"
#include "Pickup.h"
#include <iostream>


Monster::Monster()
{
	std::cout << "Constructing Monster" << std::endl;
	rectangle.setSize(sf::Vector2f(16, 16));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(500, 100);
	noLevelCollision = true;
	friendly = false;
	contained = false;
	name = "Monster";
}


Monster::~Monster()
{
}

void Monster::collideWith()
{
	std::vector<GameObject*> data;
	//level
	data = gameData->getList(0);
	data.at(0)->collision(this);
	//projectile
	data = gameData->getList(4);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
}


void Monster::collided(GameObject *other)
{
	std::string otherName = other->getName();
	if (other->isFriendly())
	{
		death();
		if (otherName.find("Projectile"))
			captured(other);
	}
}


void Monster::captured(GameObject *other)
{
	//change animation and behavior.
	contained = true;
}


void Monster::levelStart()
{
	setVelocity(0, SCREEN_MULTIPLIER);
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
		collideWith();
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