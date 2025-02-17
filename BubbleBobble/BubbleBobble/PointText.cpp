#include "stdafx.h"
#include "PointText.h"
#include <iostream>

PointText::PointText()
{
	name = "PointText";
	window = nullptr;
	gameData = nullptr;
}


PointText::PointText(sf::RenderWindow *win, GameData *data,  GameObject *creator, unsigned int value, bool big)
{
	window = win;
	gameData = data;

	rectangle.setSize(sf::Vector2f(8 * 6, 8 * 2));
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2, rectangle.getLocalBounds().height / 2);

	std::string fileName = "../textures/PointText/" + value;
	if (big)
		fileName += "-big";

	if (creator->getName() == "Bubblun")
		fileName += "-green";
	else
		fileName += "-blue";
	fileName += "-points.png";
	name = fileName;

	if (!texture.loadFromFile(fileName))
	{
		std::cout << "Failed to load " << fileName;
		rectangle.setFillColor(sf::Color::Cyan);
	}
	else
		rectangle.setTexture(&texture);

	sf::FloatRect creatorRect = creator->getRectangle().getGlobalBounds();
	rectangle.setPosition(creatorRect.left, creatorRect.top);
	setVelocity(0, -1 * SCREEN_MULTIPLIER);
	startPedometer(40);
}


PointText::~PointText()
{
}

void PointText::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(5, temp);
}