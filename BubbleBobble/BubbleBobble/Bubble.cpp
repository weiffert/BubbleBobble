#include "stdafx.h"
#include "Bubble.h"
#include "Monster.h"
#include <iostream>


Bubble::Bubble(sf::RenderWindow * win, GameData * dat, Player * player) : Projectile(win, dat)
{
	name = "Bubble";
	gameData = dat;
	window = win;
	monsterContained = nullptr;

	setTexture("../textures/Projectile/bubble.png");
	sf::Vector2f playerPos = player->getRectangle().getPosition();
	rectangle.setPosition(playerPos.x + player->getDirection() * player->getRectangle().getSize().x, playerPos.y);
	setVelocity(player->getDirection() * SCREEN_MULTIPLIER * 2, 0);
	startPedometer(window->getSize().x / 4);
}


Bubble::~Bubble()
{
}


void Bubble::distanceLimitPassed()
{
	if (velocity.x != 0)
	{
		startPedometer(window->getSize().y / 2);
		setVelocity(0, -1.25 * SCREEN_MULTIPLIER);
	}
	else
	{
		if (monsterContained != nullptr)
		{
			Monster *monster = dynamic_cast<Monster *>(monsterContained);
			monsterContained = nullptr;
			monster->release();
			monster = nullptr;
		}
		pop();
	}
}


void Bubble::levelPlay()
{
	collideWith();
	rectangle.move(velocity);
	if (monsterContained != nullptr)
		monsterContained->setPosition(rectangle.getPosition().x, rectangle.getPosition().y);
}


//Perform the pathing function. Passed in are the values of the level collision.
std::vector<bool> Bubble::levelPathing(std::vector<int> horizontal, std::vector<int> vertical)
{
	std::vector<bool> collisionOccurances;
	collisionOccurances.push_back(false);
	collisionOccurances.push_back(false);

	for (int i = 0; i < horizontal.size(); i++)
	{
		if (horizontal.at(i) == 1)
		{
			collisionOccurances.at(0) = true;
			reverseDirectionHorizontal();
		}
	}

	for (int i = 0; i < vertical.size(); i++)
	{
		if (vertical.at(i) == 1)
		{
			collisionOccurances.at(1) = true;
			velocity.y = 0;
		}
	}

	return collisionOccurances;
}


void Bubble::collided(GameObject * other)
{
	if (other->getName() == "Bubble")
	{
		Bubble *otherBubble = dynamic_cast<Bubble*>(other);
		if (!life)
		{
			pop();
		}
	}
	else if (other->getName().find("Monster") != std::string::npos && monsterContained == nullptr && velocity.x != 0)//if monster
	{
		//The substring is for getting rid of the monster part of the name.
		setTexture("../textures/CapturedMonsters/" + other->getName().substr(8) + ".png");
		monsterContained = other;
		Monster *monster = dynamic_cast<Monster *>(other);
		monster->captured(this);
		monster = nullptr;
	}
	else if (other->getName().find("Player") != std::string::npos)
	{
		pop();
	}
}


void Bubble::pop()
{
	if (monsterContained != nullptr)
	{
		monsterContained->death();
		monsterContained = nullptr;
	}

	//perform popping sequence.
	
	life = false;
	startClock(sf::milliseconds(10));
}