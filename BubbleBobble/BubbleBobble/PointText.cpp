#include "stdafx.h"
#include "PointText.h"


PointText::PointText()
{
}


PointText::PointText(std::string str, GameObject *creator)
{
	text.setString(str);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(10);
	//no setFont();
	sf::FloatRect creatorRect = creator->getRectangle().getGlobalBounds();
	text.setPosition(creatorRect.left, creatorRect.top);
	setVelocity(0, -1);
	setPedometerLimit(40);
	startPedometer();
}


PointText::~PointText()
{
}


void PointText::rend