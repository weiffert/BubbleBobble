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


Level::Level()
{
}


Level::Level(std::string id)
{
	std::cout << "Constructing Level" << std::endl;
	name = id;
	setTexture("../textures/Levels/" + name + "/" + name + ".png");
	bitmapMaker();
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
	time();
}


void Level::levelTransition()
{
	rectangle.move(velocity);
	distance();
}

void Level::timeLimitPassed()
{
	std::cout << "Transitioning Level From " << name << std::endl;
	levelEnd();

	GameObject *nextLevel = nullptr;
	int nextLevelNumber = std::stoi(name.substr(name.find_last_of("l") + 1)) + 1;

	if (nextLevelNumber <= 8)
		nextLevel = new Level("Level" + std::to_string(nextLevelNumber));
	else
		//Quit game.
		int i = 0;

	nextLevel->initialize(window, gameData);
	nextLevel->setPosition(0, window->getSize().y );// - nextLevel->getRectangle().getLocalBounds().height);
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

void Level::distanceLimitPassed()
{
	if (offTop())
		death();
	else
		levelStart();
}

void Level::levelEnd()
{
	transition = true;
	setVelocity(0, -1 * SCREEN_MULTIPLIER);
	startPedometer(window->getSize().y);
}

void Level::levelStart()
{
	transition = false;
	setVelocity(0, 0); 

	std::vector<GameObject *> players = gameData->getList(1);
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->levelStart();
	}

	for (int i = 0; i < BITMAP_WIDTH; i++)
	{
		for (int j = 0; j < BITMAP_HEIGHT; j++)
		{
			GameObject *newMonster = nullptr;
			enum monsterTypes {ZENCHAN = 1, MIGHTA, MONSTA, PULPUL, BANEBOU, HIDEGONS, DRUNK, INVADER, SUPER_DRUNK};
			switch (monsterSpawns[i][j])
			{
			case ZENCHAN:
				newMonster = new Zenchan();
				break;
			case MIGHTA:
				newMonster = new Mighta();
				break;
			case MONSTA:
				newMonster = new Monsta();
				break;
			case PULPUL:
				newMonster = new Pulpul();
				break;
			case BANEBOU:
				newMonster = new Banebou();
				break;
			case HIDEGONS:
				newMonster = new Hidegons();
				break;
			case DRUNK:
				newMonster = new Drunk();
				break;
			case INVADER:
				newMonster = new Invader();
				break;
			case SUPER_DRUNK:
				newMonster = new SuperDrunk();
				break;
			}

			if (newMonster != nullptr)
			{
				newMonster->initialize(window, gameData);
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
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}

void Level::collision(GameObject *other)
{
	if (other->getVelocity().x != 0 || other->getVelocity().y != 0)
	{
		std::vector<int> horizontal, vertical;
		const int CONVERTER = 8 * SCREEN_MULTIPLIER;

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

		//int xval = corner.x;
		//int yval = corner.y;
		corner.x /= CONVERTER;
		corner.y /= CONVERTER; 
		
		//std::cout << "(" << corner.x << ", " << corner.y << ") : " << std::endl << std::endl;

		if (std::floor(moving.getGlobalBounds().left / CONVERTER) != std::floor(rect.getGlobalBounds().left / CONVERTER))
		{
			//std::cout << "HORIZONTAL: " << std::endl;
			for (int i = 0; i <= height / CONVERTER; i++)
			{
				//std::cout << "(" << corner.x << ", " << corner.y + -1 * multiplierY * i << ") : " << bitmap[corner.x][corner.y + -1 * multiplierY * i] << std::endl;
				horizontal.push_back(bitmap[corner.x][corner.y + -1 * multiplierY * i]);
			}
			//std::cout << std::endl;
		}

		if (std::floor(moving.getGlobalBounds().top / CONVERTER) != std::floor(rect.getGlobalBounds().top / CONVERTER))
		{
			//std::cout << "VERTICAL: " << std::endl;
			for (int i = 0; i <= width / CONVERTER; i++)
			{
				//std::cout << "(" << corner.x + -1 * multiplierX * i << ", " << corner.y << ") : "	<< bitmap[corner.x + -1 * multiplierX * i][corner.y] << std::endl;
				vertical.push_back(bitmap[corner.x + -1 * multiplierX * i][corner.y]);
			}
			//std::cout << std::endl;
		}

		bool verticalCollision = false;

		if (other->isFriendly())
		{
			/*
			window->clear();

			window->draw(rectangle);
			window->draw(rect);
			window->draw(moving);

			sf::RectangleShape cornerONE;
			cornerONE.setSize(sf::Vector2f(4, 4));
			cornerONE.setOrigin(2, 2);
			sf::Vector2f vector;
			vector.x = xval;
			vector.y = yval;
			cornerONE.setPosition(vector);
			cornerONE.setFillColor(sf::Color::Magenta);
			window->draw(cornerONE);

			cornerONE.setSize(sf::Vector2f(4, 4));
			cornerONE.setOrigin(2, 2);
			vector.x = center.x;
			vector.y = center.y;
			cornerONE.setPosition(vector);
			cornerONE.setFillColor(sf::Color::Blue);
			window->draw(cornerONE);

			window->display();
			*/

			//Interpret.
			for (int i = 0; i < horizontal.size(); i++)
			{
				enum type { Wall = 1 };
				switch (horizontal.at(i))
				{
				case Wall:
					other->velocityToNextGridLine(true);
				}
			}
			for (int i = 0; i < vertical.size(); i++)
			{
				enum type { Floor = 2, MonsterFloor, EdgeFloor };
				switch (vertical.at(i))
				{
				case Floor:
				case MonsterFloor:
				case EdgeFloor:
					if (other->getVelocity().y > 0)
					{
						verticalCollision = true;
						other->velocityToNextGridLine(false);
					}
				}
			}
		}

		if (!verticalCollision)
		{
			if (center.y - height / 2 > rectangle.getGlobalBounds().top + rectangle.getLocalBounds().height)
				other->changePositionVertical(-1 * rectangle.getLocalBounds().height - height);
			else if (center.y + height / 2 < rectangle.getGlobalBounds().top)
				other->changePositionVertical(rectangle.getLocalBounds().height);
		}

	}
}

void Level::bitmapMaker()
{
	std::fstream input;
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

void Level::enemyCheck()
{
	//if no enemies left
	if (!(gameData->exist(2)))
	{
		std::cout << "Starting Level Transition Clock" << std::endl;
		startClock(sf::seconds(5));
	}
}