#include "stdafx.h"
#include "PointText.h"


PointText::PointText()
{
}


PointText::PointText(std::string str, GameObject *creator)
{
	sf::FloatRect creatorRect = creator->getRectangle().getGlobalBounds();
	rectangle.setPosition(creatorRect.left, creatorRect.top);
	//texture.loadFromFile();
	//rectangle.setTexture(texture);
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