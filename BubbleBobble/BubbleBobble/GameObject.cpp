#include "stdafx.h"
#include "GameObject.h"
#include <math.h>
#include <iostream>


GameObject::GameObject()
{
	//add instance variables

}


GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (trackingTime)
	{
		time();
	}
	if (trackingDistance)
	{
		distance();
	}
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
	if (clock.getElapsedTime() > timeLimit)
	{
		stopClock();
		timeLimitPassed();
	}
}

/*Updates pedometer to be the absolute value of the distance traveled along the 
hypotnuse from the velocity.*/
void GameObject::distance()
{
	pedometer += std::abs(std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y));
	
	if (pedometer > distanceLimit)
	{
		stopPedometer();
		distanceLimitPassed();
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

}
void GameObject::timeLimitPassed()
{

}
void GameObject::distanceLimitPassed()
{

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


//Set variables
void GameObject::setName(std::string set)
{
	name = set;
}
void GameObject::setVelocity(sf::Vector2f set)
{
	velocity = set;
}
void GameObject::velocityToNextGridLine(bool horizontal)
{
	if (horizontal)
	{
		sf::Vector2f newVelocity;
		newVelocity.x = std::floor(rectangle.getPosition().x / 8) * 8 - rectangle.getPosition().x;
		newVelocity.y = getVelocity().y;
		setVelocity(newVelocity);
	}
	else
	{
		sf::Vector2f newVelocity;
		newVelocity.y = std::floor(rectangle.getPosition().y / 8) * 8 - rectangle.getPosition().y;
		newVelocity.x = getVelocity().x;
		setVelocity(newVelocity);
	}
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