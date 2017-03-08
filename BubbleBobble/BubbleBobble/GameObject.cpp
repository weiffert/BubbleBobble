#include "stdafx.h"
#include "GameObject.h"
#include <math.h>


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
void GameObject::collision(GameObject)
{
	//if collision, call collided();
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


//Set variables
void GameObject::setName(std::string set)
{
	name = set;
}
void GameObject::setVelocity(sf::Vector2f set)
{
	velocity = set;
}
void GameObject::setTimeLimit(sf::Time set)
{
	timeLimit = set;
}
void GameObject::setPedometerLimit(float set)
{
	distanceLimit = set;
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
double GameObject::stopClock()
{
	trackingTime = false;
	timeElapsed = clock.getElapsedTime();
}
double GameObject::stopPedometer()
{
	trackingDistance = false;
}