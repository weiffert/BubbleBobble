#include "stdafx.h"
#include "GameObject.h"
#include <math.h>
#include <iostream>


GameObject::GameObject()
{
	//add instance variables
	gameData = nullptr;
	window = nullptr; 
	velocity.x = 0;
	velocity.y = 0;

	//Clock variables.
	timeElapsed = sf::seconds(0);
	timeLimit = sf::seconds(0);
	trackingTime = false;

	//Distance variables.
	pedometer = 0;
	distanceElapsed = 0;
	distanceLimit = 0;
	trackingDistance = false;

	name = "none";
	life = false;
	levelTransition = false;
}

GameObject::GameObject(std::string set)
{
	name = set;
}

GameObject::~GameObject()
{
}


void GameObject::update()
{
	updateVelocity();
	time();
	distance();
	collideWith();
}


void GameObject::collideWith()
{

}


void GameObject::updateVelocity()
{
	//any change.
	//check for collision.
	gameData->getList(0).at(0)->collision(this);
	//move.
	rectangle.move(velocity);
}

//Game Logic
//Simple Collision.
void GameObject::collision(GameObject *other)
{
	if (rectangle.getGlobalBounds().intersects(other->getRectangle().getGlobalBounds()))
	{
		collided();
		other->collided();
	}
}

//Returns true and stops the timer 
void GameObject::time()
{
	if (trackingTime && clock.getElapsedTime() > timeLimit)
	{
		stopClock();
		timeLimitPassed();
	}
}

/*Updates pedometer to be the absolute value of the distance traveled along the 
hypotnuse from the velocity.*/
void GameObject::distance()
{
	if (trackingDistance)
	{
		pedometer += std::abs(std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y));

		if (pedometer > distanceLimit)
		{
			stopPedometer();
			distanceLimitPassed();
		}
	}
}

void GameObject::render()
{
	window->draw(rectangle);
}


//Specific event type functions.
void GameObject::collided()
{

}
void GameObject::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}

void GameObject::levelEnd()
{
	levelTransition = true;
}

void GameObject::levelStart()
{
	levelTransition = false;
}

void GameObject::timeLimitPassed()
{
	death();
}
void GameObject::distanceLimitPassed()
{
	death();
}

//get variables.
std::string GameObject::getName()
{
	return name;
}
sf::Vector2f GameObject::getVelocity()
{
	return velocity;
}
sf::Time GameObject::getTimeElapsed()
{
	if (trackingTime)
		return clock.getElapsedTime();
	return timeElapsed;
}
float GameObject::getDistanceElapsed()
{
	return pedometer;
}
sf::RectangleShape GameObject::getRectangle()
{
	return rectangle;
}
sf::Texture GameObject::getTexture()
{
	return texture;
}
bool GameObject::isTransitioningLevels()
{
	return levelTransition;
}


//Set variables
void GameObject::setName(std::string set)
{
	name = set;
}
void GameObject::setVelocity(sf::Vector2f set)
{
	velocity = set;
}
void GameObject::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}
void GameObject::velocityToNextGridLine(bool horizontal)
{
	sf::Vector2f newVelocity;
	float forwards, backwards;

	if (horizontal)
	{
		forwards = std::floor(rectangle.getPosition().x / 8) * 8 - rectangle.getPosition().x;
		backwards = (std::floor(rectangle.getPosition().x / 8) + 1) * 8 - rectangle.getPosition().x;
		if (backwards > forwards)
			newVelocity.x = forwards;
		else
			newVelocity.x = backwards;
		newVelocity.y = getVelocity().y;
	}
	else
	{
		forwards = std::floor(rectangle.getPosition().y / 8) * 8 - rectangle.getPosition().y;
		backwards = (std::floor(rectangle.getPosition().y / 8) + 1) * 8 - rectangle.getPosition().y;
		if (backwards > forwards)
			newVelocity.y = forwards;
		else
			newVelocity.y = backwards; 
		newVelocity.x = getVelocity().x;
	}
	setVelocity(newVelocity);
}
void GameObject::setTimeLimit(sf::Time set)
{
	timeLimit = set;
}
void GameObject::setPedometerLimit(float set)
{
	distanceLimit = set;
}
void GameObject::setRenderWindow(sf::RenderWindow *set)
{
	window = set;
}
void GameObject::setAnimation(std::string type)
{
	if (type == "")
	{
		animations.push_back(Animation(&texture, sf::Vector2u(1,0), 0, 0));
	}
}
void GameObject::setPosition(float x, float y)
{
	rectangle.setPosition(x, y);
}

void GameObject::startClock()
{
	trackingTime = true;
	clock.restart();
}
void GameObject::startPedometer()
{
	trackingDistance = true;
	pedometer = 0;
}
sf::Time GameObject::stopClock()
{
	trackingTime = false;
	timeElapsed = clock.getElapsedTime();
	return timeElapsed;
}
double GameObject::stopPedometer()
{
	trackingDistance = false;
	return pedometer;
}

bool GameObject::offTop()
{
	if (rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height < 0)
		return true;
	return false;
}
bool GameObject::offBottom()
{
	if (rectangle.getGlobalBounds().top > window->getSize().y)
		return true;
	return false;
}

void GameObject::setGameDataPTR(GameData *set)
{
	gameData = set;
}