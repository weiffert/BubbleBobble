#include "stdafx.h"
#include "PointText.h"


PointText::PointText()
{
}


PointText::PointText(std::string str, GameObject *creator)
{
	rectangle.setSize(sf::Vector2f(8 * 6, 8 * 2));
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2, rectangle.getLocalBounds().height / 2);

	//texture.loadFromFile();
	//rectangle.setTexture(texture);

	sf::FloatRect creatorRect = creator->getRectangle().getGlobalBounds();
	rectangle.setPosition(creatorRect.left, creatorRect.top);
	setVelocity(0, -1);
	setPedometerLimit(40);
	startPedometer();
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