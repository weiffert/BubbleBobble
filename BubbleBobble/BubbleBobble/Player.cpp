#include "stdafx.h"
#include "Player.h"
#include "Skel_Monsta.h"


Player::Player()
{

}


Player::~Player()
{
}

void Player::updateVelocity()
{
	if (levelTransition)
	{
		//move to the corner
	}
	else
	{
		//standard update.
		gameData->getList(0).at(0)->collision(this);
		rectangle.move(velocity);
	}
}

void Player::levelEnd()
{
	levelTransition = true;
	//change animation.
}

void Player::levelStart()
{
	levelTransition = false;
	setTimeLimit(sf::seconds(30));
	startClock();
	//change animation.
}

void Player::timeLimitPassed()
{
	//Show hurry up text?
	//Begin pursuit of skel monsta.
	GameObject *skelMonsta = new Skel_Monsta();
	gameData->add(2, skelMonsta);
}

//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}