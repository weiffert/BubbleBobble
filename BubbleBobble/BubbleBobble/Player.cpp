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
	std::vector<GameObject*> data;
	//level
	data = gameData->getList(0);
	data.at(0)->collision(this);
	//pickups
	data = gameData->getList(3);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
	//projectile
	data = gameData->getList(4);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
	//monsters
	data = gameData->getList(2);
	for (int i = 0; i < data.size(); i++)
		collision(data.at(i));
}


void Player::collided(GameObject *other)
{
	std::string otherName = other->getName();
	if (other->isFriendly())
	{
		if (otherName == "Projectile")
			//do different stuff for top and bottom.
			int i = 0;
		if (otherName == "Pickup")
			pickedUp(other);
	}
	else
	{
		death();
	}
}


void Player::pickedUp(GameObject *other)
{
	//add to score.
	//any powerups?
}


void Player::levelPlay()
{
	//standard update.
	collideWith();
	rectangle.move(velocity);
	time();
	distance();
}


void Player::levelTransition()
{
	//move to corner
	sf::Vector2f corner;

	corner.y = 8 * 25 * 4;
	if (name == "Player2")
		corner.x = 8 * 29 * 4;
	else
		corner.x = 8 * 3 * 4;

	sf::Vector2f player;
	player.x = rectangle.getGlobalBounds().left * 4;
	player.y = rectangle.getGlobalBounds().top * 4;
	float differenceX = corner.x - player.x;
	float differenceY = corner.y - player.y;

	if (differenceX < 0)
		velocity.x = -4;
	else if (differenceX == 0)
		velocity.x = 0;
	else
		velocity.x = 4;

	if (differenceY < 0)
		velocity.y = -4;
	else if (differenceY == 0)
		velocity.y = 0;
	else
		velocity.y = 4;

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
<<<<<<< HEAD
	setVelocity((4 * -1), velocity.y);
=======
	setVelocity((1 * -1), velocity.y);
	direction = -1;//move towards negative x
>>>>>>> origin/master
}


void Player::moveRight()
{
<<<<<<< HEAD
	setVelocity(4, velocity.y);
=======
	setVelocity(1, velocity.y);
	direction = 1;//move towards positive x
>>>>>>> origin/master
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