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
	name = id;
	if (!texture.loadFromFile("../textures/Levels/" + name + "/" + name + ".png"))
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << ".png" << std::endl;
	else
	{
		rectangle.setTexture(&texture);
		sf::Vector2f vec;
		vec.x = texture.getSize().x;
		vec.y = texture.getSize().y;
		rectangle.setSize(vec);
		rectangle.setPosition(0, 16);
	}
	bitmapMaker();
}


Level::~Level()
{
	std::cout << "Deconstructing Level" << std::endl;
}

void Level::update()
{
	if (!transition)
		levelPlay();
	else
		levelTransition();
	distance();
	//collideWith();
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
}

void Level::timeLimitPassed()
{
	std::cout << "Transitioning Level From " << name << std::endl;
	levelEnd();

	GameObject *nextLevel = new Level("Level" + std::to_string((std::stoi(name.substr(name.find_last_of("l") + 1)) + 1)));
	nextLevel->initialize(window, gameData);
	nextLevel->setPosition(0, rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height);
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
	{
		death();
		gameData->getList(0).at(1)->levelStart();
	}
}

void Level::levelEnd()
{
	transition = true;
	setVelocity(0, 1);
	setPedometerLimit(window->getSize().y / 4);
	startPedometer();
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
				newMonster->levelStart();
				newMonster->setPosition(i * 8, 0 - newMonster->getRectangle().getLocalBounds().height);
				newMonster->setPedometerLimit(j * 8);

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
	if (velocity.x || velocity.y)
	{
		std::vector<int> horizontal, vertical;

		int multiplierX = 1, multiplierY = 1;
		sf::RectangleShape rect = other->getRectangle();
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

		if (std::floor(moving.getGlobalBounds().left / 8) != std::floor(rect.getGlobalBounds().left / 8))
		{
			for (int i = 0; i < height / 8; i++)
			{
				horizontal.push_back(bitmap[corner.x][corner.y + multiplierY * i]);
			}
		}

		if (std::floor(moving.getGlobalBounds().top / 8) != std::floor(rect.getGlobalBounds().top / 8))
		{
			for (int i = 0; i < height / 8; i++)
			{
				vertical.push_back(bitmap[corner.x + -1 * multiplierX * i][corner.y]);
			}
		}

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
			enum type { Floor = 2 };
			switch (vertical.at(i))
			{
			case Floor:
				if (other->getVelocity().y < 0)
					other->velocityToNextGridLine(false); 
			}
		}

		if (other->getName().find("monster"))
		{

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
	if (!(gameData->exist(3)))
	{
		std::cout << "Starting Level Transition Clock" << std::endl;
		setTimeLimit(sf::seconds(5));
		startClock();
	}
}