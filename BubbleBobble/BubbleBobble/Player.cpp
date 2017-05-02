#include "stdafx.h"
#include "Player.h"
#include "Skel_Monsta.h"
#include <iostream>


Player::Player()
{
	setLives(3);
	name = "Player";
	window = nullptr;
	gameData = nullptr;
}


Player::Player(std::string set, sf::RenderWindow *win, GameData *data)
{
	//assign instance variables values
	setName(set);//player name
	window = win;//render window reference
	gameData = data;//reference to other game data

	setLives(3);//players have 3 lives

	//set the corresponsing texture to player
	if (set == "Player1")
		setTexture("../textures/Characters/bubblun.png");
	else if (set == "Player2")
	{
		setTexture("../textures/Characters/bobblun.png");
		direction = -1;
		setPosition(window->getSize().x - (16 * SCREEN_MULTIPLIER), 0);
	}
	flipTexture();//init texture flip to face the correct way
}


Player::~Player()
{
}


void Player::update()
{
	if (!transition)//if player not in transition
		levelPlay();//trigger player update events
	else//otherwise
		levelTransition();//player is in transition

	if (getLivesRemaining() <= 0)//if player has no remaining lives
		death();
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
	//collision with friendly
	if (other->isFriendly())
	{
		if (otherName == "Projectile")
			//do different stuff for top and bottom.
			int i = 0;
		if (otherName == "Pickup")
			pickedUp(other);
	}
	//collision with hostile
	else
	{
		setLives(getLivesRemaining() - 1);
		std::cout << "Lives remaining : " << getLivesRemaining() << std::endl;

		//kill player if there is no lives left
		if (getLivesRemaining() <= 0)
		{
			life = false;
			std::cout << "PLAYER IS DEAD!" << std::endl;
		}
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

	corner.y = 8 * 24 * SCREEN_MULTIPLIER - 1;
	if (name == "Player2")
		corner.x = 8 * 28 * SCREEN_MULTIPLIER;
	else
		corner.x = 8 * 3 * SCREEN_MULTIPLIER;

	sf::Vector2f player;
	player.x = rectangle.getGlobalBounds().left;
	player.y = rectangle.getGlobalBounds().top;
	int differenceX = std::floor((corner.x - player.x) / BITMAP_CONVERTER) * BITMAP_CONVERTER;
	int differenceY = std::floor((corner.y - player.y) / BITMAP_CONVERTER) * BITMAP_CONVERTER;

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

	//face the cahracter the correct way during transition
	if (getName() == "Player1")
		direction = 1;
	else
		direction = -1;

	flipTexture();
}


void Player::levelStart()
{
	transition = false;
	//Skel_Monsta time limit.
	startClock(sf::seconds(30));
	direction = 1;

	//Velocity set.
	setVelocity(0, 0);
	gravity();

	//change animation.
}


void Player::timeLimitPassed()
{
	//Show hurry up text?
	//Begin pursuit of skel monsta.
	GameObject *skelMonsta = new Skel_Monsta(window, gameData);
	gameData->add(2, skelMonsta);
}


//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}