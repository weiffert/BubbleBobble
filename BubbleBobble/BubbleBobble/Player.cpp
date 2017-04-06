#include "stdafx.h"
#include "Player.h"
#include "Skel_Monsta.h"
#include <iostream>


Player::Player()
{
	direction = 1;//facing towards positive x
}


Player::Player(std::string set)
{
	setName(set);
	rectangle.setSize(sf::Vector2f(16, 16));
	rectangle.setFillColor(sf::Color::Green);
}


Player::~Player()
{
}


void Player::collideWith()
{
	//projectiles
	std::vector<GameObject*> data = gameData->getList(4);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
	//monsters
	data = gameData->getList(2);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
	//pickups
	data = gameData->getList(3);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
}


void Player::levelPlay()
{
	//standard update.
	gameData->getList(0).at(0)->collision(this);
	rectangle.move(velocity);
}


void Player::levelTransition()
{
	//move to corner
	sf::Vector2f corner;

	corner.y = 8 * 25;
	if (name == "Player2")
		corner.x = 8 * 29;
	else
		corner.x = 8 * 3;

	sf::Vector2f player;
	player.x = rectangle.getGlobalBounds().left;
	player.y = rectangle.getGlobalBounds().top;
	float differenceX = corner.x - player.x;
	float differenceY = corner.y - player.y;

	if (differenceX < 0)
		velocity.x = -1;
	else if (differenceX == 0)
		velocity.x = 0;
	else
		velocity.x = 1;

	if (differenceY < 0)
		velocity.y = -1;
	else if (differenceY == 0)
		velocity.y = 0;
	else
		velocity.y = 1;

	rectangle.move(velocity);
}


void Player::levelEnd()
{
	transition = true;
	//change animation.
}


void Player::levelStart()
{
	transition = false;
	setTimeLimit(sf::seconds(30));
	startClock();
	//change animation.
}


void Player::timeLimitPassed()
{
	//Show hurry up text?
	//Begin pursuit of skel monsta.
	GameObject *skelMonsta = new Skel_Monsta();
	skelMonsta->initialize(window, gameData);
	gameData->add(2, skelMonsta);
}


//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}


void Player::moveLeft()
{
	setVelocity((1 * -1), velocity.y);
	direction = -1;//move towards negative x
}


void Player::moveRight()
{
	setVelocity(1, velocity.y);
	direction = 1;//move towards positive x
}


void Player::stopHorizontalVelocity()
{
	setVelocity(0, velocity.y);
}

void Player::jump()
{
	setVelocity(getVelocity().x, 1);
}


void Player::stopXMovement()
{
	setVelocity(0, getVelocity().y);
}


void Player::stopYMovement()
{
	setVelocity(getVelocity().x, 0);
}

int Player::getDirection()
{
	return direction;
}