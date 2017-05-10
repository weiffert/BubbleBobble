#include "stdafx.h"
#include "Monster.h"
#include "Pickup.h"
#include <iostream>


Monster::Monster()
{
	window = nullptr;
	gameData = nullptr;
	name = "Monster";
	rectangle.setSize(sf::Vector2f(16, 16));
	//rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(500, 100);
	noLevelCollision = true;
	friendly = false;
	direction = -1;//move towards negative x
	bubbleContainer = nullptr;
}


Monster::Monster(sf::RenderWindow *win, GameData *data)
{
	window = win;
	gameData = data;
	name = "Monster";
	rectangle.setSize(sf::Vector2f(16, 16));
	//rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(500, 100);
	noLevelCollision = true;
	friendly = false;
	direction = -1;//move towards negative x
	bubbleContainer = nullptr;
}


Monster::~Monster()
{
	std::cout << name << " died" << std::endl;
}


void Monster::collideWith()
{
	if (bubbleContainer == nullptr)
	{
		std::vector<GameObject*> data;
		//level
		data = gameData->getList(0);
		data.at(0)->collision(this);
		//projectile
		data = gameData->getList(4);
		for (int i = 0; i < data.size(); i++)
			if (data.at(i)->isFriendly())
				collision(data.at(i));
	}
}


void Monster::collided(GameObject *other)
{
	if (bubbleContainer != nullptr)
		if (other->isFriendly())
			if (other->getName().find("Bubble") == std::string::npos)
				death();
}


void Monster::captured(GameObject *other)
{
	//change animation and behavior.
	bubbleContainer = other;
	//Sets the rectangle to be transparent.
	//rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	rectangle.setFillColor(sf::Color(255, 0, 255));
}


void Monster::release()
{
	bubbleContainer = nullptr;
	rectangle.setFillColor(sf::Color::Transparent);
}


void Monster::levelStart()
{
	setVelocity(0, SCREEN_MULTIPLIER);
}


void Monster::levelPlay()
{
	if (!noLevelCollision)
	{
		if (bubbleContainer == nullptr)
		{
			//any change.
			//check for collision.
			collideWith();
			//move.
			rectangle.move(velocity);
		}
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

	//pickup creation. Something like this.
	temp = new Pickup(window, gameData);
	gameData->add(3, temp);
}

void Monster::distanceLimitPassed()
{
	noLevelCollision = false;
	setVelocity(1 * SCREEN_MULTIPLIER, -1 * SCREEN_MULTIPLIER);
}


/*
void Monster::levelPathing()
{
	if (gameData->getList(1).size() > 0)
	{
		GameObject *player = gameData->getList(1).at(0);
		sf::Vector2f playerPosition;
		sf::RectangleShape playerRect = player->getRectangle();
		playerPosition.x = playerRect.getGlobalBounds().left + playerRect.getSize().x / 2;
		playerPosition.y = playerRect.getGlobalBounds().top + playerRect.getSize().y;

		if (playerPosition.y > rectangle.getGlobalBounds().top + rectangle.getSize().y)
			upMovement = true;
		else
			upMovement = false;
		if (playerPosition.x < rectangle.getGlobalBounds().left + rectangle.getSize().x / 2)
			leftMovement = true;
		else
			leftMovement = false;
	}
}
*/