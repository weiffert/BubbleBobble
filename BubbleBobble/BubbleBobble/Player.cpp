#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::levelTransition()
{
	//change animation.
	//move to respective corner.
}

//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}