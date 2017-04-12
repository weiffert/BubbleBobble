#include "stdafx.h"
#include "Player.h"
#include "Skel_Monsta.h"
#include <iostream>


Player::Player()
{
	std::cout << "Constructing Player" << std::endl;
	direction = 1;//facing towards positive x
}


Player::Player(std::string set)
{
	std::cout << "Constructing Player" << std::endl;
	setName(set);
	setTexture("../textures/bubblun.png");
}


Player::~Player()
{
}


void Player::update()
{
	if (!transition)
		levelPlay();
	else
		levelTransition();
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
		std::cout << "PLAYER IS DEAD!" << std::endl;
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
	gravity();
	collideWith();
	rectangle.move(velocity);
	time();
	distance();
}


void Player::levelTransition()
{
	//move to corner
	sf::Vector2f corner;

	corner.y = 8 * 23 * SCREEN_MULTIPLIER;
	if (name == "Player2")
		corner.x = 8 * 29 * SCREEN_MULTIPLIER;
	else
		corner.x = 8 * 3 * SCREEN_MULTIPLIER;

	sf::Vector2f player;
	player.x = rectangle.getGlobalBounds().left;
	player.y = rectangle.getGlobalBounds().top;
	float differenceX = corner.x - player.x;
	float differenceY = corner.y - player.y;

	if (differenceX < 0)
		velocity.x = -1 * SCREEN_MULTIPLIER;
	else if (differenceX == 0)
		velocity.x = 0;
	else
		velocity.x = SCREEN_MULTIPLIER;

	if (differenceY < 0)
		velocity.y = -1 * SCREEN_MULTIPLIER;
	else if (differenceY == 0)
		velocity.y = 0;
	else
		velocity.y = SCREEN_MULTIPLIER;

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
	//Skel_Monsta time limit.
	startClock(sf::seconds(30));

	//Velocity set.
	setVelocity(0, 0);
	gravity();

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