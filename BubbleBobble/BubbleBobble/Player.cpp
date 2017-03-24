#include "stdafx.h"
#include "Player.h"


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
	//change animation.
}

//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}