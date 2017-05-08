#include "stdafx.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include "Zenchan.h"
#include "Mighta.h"
#include "Monsta.h"
#include "Pulpul.h"
#include "Banebou.h"
#include "Hidegons.h"
#include "Drunk.h"
#include "Invader.h"
#include "SuperDrunk.h"
#include <Windows.h>


Level::Level()
{
	name = "Level";
	window = nullptr;
	gameData = nullptr;
}


Level::Level(std::string id, sf::RenderWindow *win, GameData *data)
{
	name = id;
	window = win;
	gameData = data;
	//Load the texture and bitmap according to the level name.
	setTexture("../textures/Levels/" + name + "/" + name + ".png");
	bitmapMaker();
	menuReturn = false;
}


Level::~Level()
{
}

void Level::update()
{
	if (!transition)
		levelPlay();
	else
		levelTransition();
}


void Level::levelPlay()
{
	if (!trackingTime)
		enemyCheck();
	else
		time();
}


void Level::levelTransition()
{
	rectangle.move(velocity);
	distance();
}


//Is called when the level transition clock is finished.
//Starts the transition sequence.
void Level::timeLimitPassed()
{
	if (name != "LevelEnd")
	{
		levelEnd();
		GameObject *nextLevel = nullptr;
		int nextLevelNumber = std::stoi(name.substr(name.find_last_of("l") + 1)) + 1;

		if (nextLevelNumber <= 8)
		{
			nextLevel = new Level("Level" + std::to_string(nextLevelNumber), window, gameData);

			nextLevel->setPosition(0, window->getSize().y);
			nextLevel->levelEnd();
			gameData->add(0, nextLevel);

			std::vector<GameObject *> players = gameData->getList(1);
			for (int i = 0; i < players.size(); i++)
			{
				players.at(i)->levelEnd();
			}

			gameData->clear(2);
			gameData->clear(3);
			gameData->clear(4);
			gameData->clear(5);
		}
		else
		{
			nextLevel = new Level("LevelEnd", window, gameData);
			gameData->clear(0);
			gameData->clear(1);
			gameData->clear(2);
			gameData->clear(3);
			gameData->clear(4);
			gameData->clear(5);
			gameData->add(0, nextLevel);
		}

	}
	else
	{
		menuReturn = true;
	}
}

bool Level::returnToMenu()
{
	return menuReturn;
}

void Level::distanceLimitPassed()
{
	if (offTop())
		death();
	else
		levelStart();
}

//Performs level ending functions for level only.
void Level::levelEnd()
{
	transition = true;
	setVelocity(0, -1 * SCREEN_MULTIPLIER);
	startPedometer(window->getSize().y);
}

//Primes the level for starting.
void Level::levelStart()
{
	transition = false;
	setVelocity(0, 0); 

	//Prime the players for starting.
	std::vector<GameObject *> players = gameData->getList(1);
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->levelStart();
	}

	//Spawn the monsters.
	for (int i = 0; i < BITMAP_WIDTH; i++)
	{
		for (int j = 0; j < BITMAP_HEIGHT; j++)
		{
			GameObject *newMonster = nullptr;
			enum monsterTypes {ZENCHAN = 1, MIGHTA, MONSTA, PULPUL, BANEBOU, HIDEGONS, DRUNK, INVADER, SUPER_DRUNK};
			switch (monsterSpawns[i][j])
			{
			case ZENCHAN:
				newMonster = new Zenchan(window, gameData);
				break;
			case MIGHTA:
				newMonster = new Mighta(window, gameData);
				break;
			case MONSTA:
				newMonster = new Monsta(window, gameData);
				break;
			case PULPUL:
				newMonster = new Pulpul(window, gameData);
				break;
			case BANEBOU:
				newMonster = new Banebou(window, gameData);
				break;
			case HIDEGONS:
				newMonster = new Hidegons(window, gameData);
				break;
			case DRUNK:
				newMonster = new Drunk(window, gameData);
				break;
			case INVADER:
				newMonster = new Invader(window, gameData);
				break;
			case SUPER_DRUNK:
				newMonster = new SuperDrunk(window, gameData);
				break;
			}

			if (newMonster != nullptr)
			{
				newMonster->setPosition(i * 8 * SCREEN_MULTIPLIER, 0 - newMonster->getRectangle().getLocalBounds().height);
				newMonster->startPedometer((j + 1) * 8 * SCREEN_MULTIPLIER + window->getSize().y - rectangle.getLocalBounds().height);
				newMonster->levelStart();
				gameData->add(2, newMonster);
			}
		}
	}

}

void Level::death()
{
	livesRemaining = 0;
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}

//Checks other against the level's bitmap.
void Level::collision(GameObject *other)
{
	//Only check if there is velocity.
	if (other->getVelocity().x != 0 || other->getVelocity().y != 0)
	{
		//Create the vectors to store values.
		std::vector<int> horizontal, vertical;

		int multiplierX = 1, multiplierY = 1;
		sf::RectangleShape rect = other->getRectangle();
		rect.move(0, -1 * rectangle.getGlobalBounds().top);
		sf::RectangleShape moving = rect;
		moving.move(other->getVelocity());

		sf::Vector2f center;
		sf::Vector2i corner;
		float width, height;
		width = moving.getLocalBounds().width;
		height = moving.getLocalBounds().height;
		center.x = moving.getGlobalBounds().left + width / 2;
		center.y = moving.getGlobalBounds().top + height / 2;

		if (other->getVelocity().x < 0)
			multiplierX = -1;
		if (other->getVelocity().y < 0)
			multiplierY = -1;

		corner.x = center.x + multiplierX * width / 2;
		corner.y = center.y + multiplierY * height / 2;

		corner.x /= BITMAP_CONVERTER;
		corner.y /= BITMAP_CONVERTER;

		if (std::floor(moving.getGlobalBounds().left / BITMAP_CONVERTER) != std::floor(rect.getGlobalBounds().left / BITMAP_CONVERTER))
		{
			for (int i = 0; i <= height / BITMAP_CONVERTER; i++)
			{
				horizontal.push_back(bitmap[corner.x][corner.y + -1 * multiplierY * i]);
			}
		}

		if (std::floor(moving.getGlobalBounds().top / BITMAP_CONVERTER) != std::floor(rect.getGlobalBounds().top / BITMAP_CONVERTER))
		{
			for (int i = 0; i <= width / BITMAP_CONVERTER; i++)
			{
				vertical.push_back(bitmap[corner.x + -1 * multiplierX * i][corner.y]);
			}
		}

		//Interpret.
		std::vector<bool> collisionOccurances = other->levelPathing(horizontal, vertical);
		
		//Switch the position on the screen for wrap around effect.
		if (!collisionOccurances.at(1))
		{
			if (center.y - height / 2 > rectangle.getGlobalBounds().top + rectangle.getLocalBounds().height)
				other->changePositionVertical(-1 * rectangle.getLocalBounds().height - height);
			else if (center.y + height / 2 < rectangle.getGlobalBounds().top)
				other->changePositionVertical(rectangle.getLocalBounds().height);
		}
	}
}

//Loads the bitmaps from files. 
void Level::bitmapMaker()
{
	std::fstream input;
	//Load the level bitmap.
	input.open("../textures/Levels/" + name + "/" + name + "base.txt");
	if (input.is_open())
	{
		int incrementX = 0;
		int incrementY = 0;
		while (!input.eof() && incrementX < BITMAP_WIDTH)
		{
			input >> bitmap[incrementX][incrementY];
			incrementY++;
			if (incrementY >= BITMAP_HEIGHT)
			{
				incrementX++;
				incrementY = 0;
			}
		}
	}
	else
	{
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "base.txt" << std::endl;;
	}
	input.close();

	//Load the monster spawns bitmap.
	input.open("../textures/Levels/" + name + "/" + name + "spawns.txt");
	if (input.is_open())
	{
		int incrementX = 0;
		int incrementY = 0;
		while (!input.eof() && incrementX < BITMAP_WIDTH)
		{
			input >> monsterSpawns[incrementX][incrementY];
			incrementY++;
			if (incrementY >= BITMAP_HEIGHT)
			{
				incrementX++;
				incrementY = 0;
			}
		}
	}
	else
	{
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "spawns.txt" << std::endl;;
	}
	input.close();
}

//Check if any enemies are left. If there 
void Level::enemyCheck()
{
	if (!(gameData->exist(2)))
	{
		std::cout << "Starting Level Transition Clock" << std::endl;
		startClock(sf::seconds(5));
	}
}