#include "stdafx.h"
#include "Level.h"
#include <iostream>
#include <fstream>


Level::Level()
{
}


Level::Level(std::string id)
{
	name = id;
	if (!texture.loadFromFile("../textures/Levels/" + name + "/" + name + "base.png"))
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "base.png";
	bitmapMaker();
}


Level::~Level()
{
}

bool Level::update()
{
	enemyCheck();
	time();
	distance();
	return life;
}

void Level::timeLimitPassed()
{
	levelTransition();
	//get next level. call levelTransition.
	//get players. call levelTransition.
}

void Level::distanceLimitPassed()
{
	if (offTop())
	{
		death();
		//get next level. call startLevel();
	}
}

void Level::levelTransition()
{
	setVelocity(0, -1);
	setPedometerLimit(window->getSize().y);
	startPedometer();
}

void Level::startLevel()
{

}

void Level::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}

void Level::collision(GameObject *other)
{
	/*if (velocity.x != 0 && velocity.y != 0)
	{
		bool horizontal = false;
		bool vertical = false;
		int multiplier = 1;
		sf::Vector2f vector = other->getVelocity();
		sf::RectangleShape rect = other->getRectangle();
		sf::RectangleShape moving = rect;
		moving.move(vector);
		sf::Vector2f corner, cornerMoving;
		corner.y = rect.getGlobalBounds().top + rect.getLocalBounds().height;
		corner.x = rect.getGlobalBounds().left;
		cornerMoving.y = moving.getGlobalBounds().top + moving.getLocalBounds().height;
		cornerMoving.x = moving.getGlobalBounds().left;
		if (velocity.x > 0)
		{
			corner.x += rect.getLocalBounds().width;
			cornerMoving.x += moving.getLocalBounds().width;
			multiplier = -1;
		}

		int increment = 0;
		do
		{
			if ((texture.copyToImage()).getPixel(cornerMoving.x, cornerMoving.y - increment) != sf::Color(0, 0, 0))
				horizontal = false;
			increment += 8;
		} while (!horizontal && increment < static_cast<int>(rect.getLocalBounds().height) % 8);
		
		if (velocity.y <= 0)
		{
			increment = 0;
			do
			{
				if ((texture.copyToImage()).getPixel(cornerMoving.x + increment * multiplier, cornerMoving.y) != sf::Color(0, 0, 0))
					vertical = false;
				increment += 8;
			} while (!vertical && increment < static_cast<int>(rect.getLocalBounds().width) % 8);
		}

		if (horizontal)
		{

		}
		if (vertical)
		{

		}
	}*/


	if (velocity.x || velocity.y)
	{
		std::vector<int> horizontal, vertical;

		int multiplierX, multiplierY = 1;
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
			switch (horizontal.at(i))
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
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "base.txt";
	}
}

void Level::enemyCheck()
{
	//if no enemies left
	if (true)
	{
		setTimeLimit(sf::seconds(5));
		startClock();
	}
}