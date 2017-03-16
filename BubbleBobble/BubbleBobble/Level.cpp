#include "stdafx.h"
#include "Level.h"


Level::Level()
{
}


Level::~Level()
{
}

void Level::collision(GameObject *other)
{
	if (velocity.x != 0 && velocity.y != 0)
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
	}
}