#include "stdafx.h"
#include "Bubble.h"
#include <iostream>


Bubble::Bubble(sf::RenderWindow * win, GameData * dat, Player * player) : Projectile(win, dat)
{
	name = "Bubble";
	gameData = dat;
	window = win;
	monsterContained = nullptr;

	setTexture("../textures/Projectile/bubble.png");
	sf::Vector2f playerPos = player->getRectangle().getPosition();
	rectangle.setPosition(playerPos.x, playerPos.y);
	setVelocity(player->getDirection() * SCREEN_MULTIPLIER * 1.25, 0);
	startPedometer(window->getSize().x / 6);
}


Bubble::~Bubble()
{
}


void Bubble::distanceLimitPassed()
{
	if (getVelocity().x != 0)
	{
		stopPedometer();
		setVelocity(0, -1.25 * SCREEN_MULTIPLIER);
	}
}


void Bubble::timeLimitPassed()
{
	return;
}


void Bubble::collided(GameObject * other)
{
	if (other->getName() == "Bubble")
	{
		//add to linked bubble list
	}
	else if (!other->isFriendly() && monsterContained == nullptr)//if monster
	{
		setTexture("../textures/CapturedMonsters/" + other->getName() + ".png");
		monsterContained = other;
	}
	else//if player
	{
		//popBubble();
	}
}


void Bubble::popBubble()
{
	

	//for(int i = linkedBubbles.size() - 1; i >= 0; i--)
		//linkedBubbles.at(i)->death();

	death();//pop this bubble
}