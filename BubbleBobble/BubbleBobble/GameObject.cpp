#include "stdafx.h"
#include "GameObject.h"
#include <math.h>
#include <iostream>


GameObject::GameObject()
{
	std::cout << "Constructing GameObject" << std::endl;
	//add instance variables
	gameData = nullptr;
	window = nullptr;
	name = "none";

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
	life = true;
	transition = false;
	friendly = true;
}

GameObject::GameObject(std::string set)
{
	std::cout << "Constructing GameObject" << std::endl;
	gameData = nullptr;
	window = nullptr;

	name = set;

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
	life = true;
	transition = false;
	friendly = true;
}

GameObject::~GameObject()
{
	std::cout << "Deconstructing GameObject " << name << std::endl;
}


void GameObject::initialize(sf::RenderWindow *win, GameData *data)
{
	window = win;
	gameData = data;
}


void GameObject::update()
{
	if (!transition)
		levelPlay();
	else
		levelTransition();
	time();
	distance();
	collideWith();
}


void GameObject::collideWith()
{
	
}


void GameObject::levelEnd()
{
	transition = true;
}


void GameObject::levelStart()
{
	transition = false;
	gravity();
}


void GameObject::levelPlay()
{
	//move.
	collideWith();
	rectangle.move(velocity);
}


void GameObject::gravity()
{
	velocity.y = 1 * SCREEN_MULTIPLIER;
}


void GameObject::levelTransition()
{
	//Do nothing.
}

//Game Logic
//Simple Collision.
void GameObject::collision(GameObject *other)
{
	if (rectangle.getGlobalBounds().intersects(other->getRectangle().getGlobalBounds()))
	{
		collided(other);
		other->collided(this);
	}
}

//Returns true and stops the timer 
void GameObject::time()
{
	if (trackingTime && clock.getElapsedTime() >= timeLimit)
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

		if (pedometer >= distanceLimit)
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
void GameObject::collided(GameObject *)
{

}
void GameObject::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
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
	return transition;
}
bool GameObject::isFriendly()
{
	return friendly;
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
	sf::Vector2f newPosition;
	float forwards, zero, multiplierX, multiplierY;
	int edge;
	const int CONVERTER = 8 * SCREEN_MULTIPLIER;
	/*
	if (horizontal)
	{
		if (velocity.x < 0)
			multiplierX = -1;
		else
			multiplierX = 1;

		/*
		zero = rectangle.getPosition().x;
		forwards = std::floor(rectangle.getPosition().x / CONVERTER) * CONVERTER;
		//zero = std::floor(rectangle.getPosition().x / CONVERTER) * CONVERTER;
		//forwards = (std::floor(rectangle.getPosition().x / CONVERTER) + multiplierX) * CONVERTER;


		if(std::abs(forwards - edge) < std::abs(zero - edge))
			newPosition.x = forwards;
		else
			newPosition.x = zero;

		edge = rectangle.getGlobalBounds().left + rectangle.getSize().x / 2 + multiplierX * rectangle.getSize().x;

		int posX = rectangle.getPosition().x;
		int integerVelX;
		integerVelX = velocity.x;
		if ((edge - integerVelX) % CONVERTER < CONVERTER / 2)
			newPosition.x = posX + multiplierX * (integerVelX % CONVERTER);
		else
			newPosition.x = posX + -1 * multiplierX * ((CONVERTER - integerVelX) % CONVERTER);

		newPosition.y = rectangle.getPosition().y;
		velocity.x = 0;
	}
	else
	{
		if (velocity.y < 0)
			multiplierY = -1;
		else
			multiplierY = 1;
		/*
		zero = std::floor(rectangle.getPosition().y / CONVERTER) * CONVERTER + 1;
		forwards = std::floor(rectangle.getPosition().y / CONVERTER) * CONVERTER;
		//zero = std::floor(rectangle.getPosition().y / CONVERTER) * CONVERTER;
		//forwards = (std::floor(rectangle.getPosition().y / CONVERTER) + multiplierY) * CONVERTER;

		edge = rectangle.getGlobalBounds().top + rectangle.getSize().y;

		if (std::abs(forwards - edge) < std::abs(zero - edge))
			newPosition.y = forwards;
		else
			newPosition.y = zero;

		int posY = rectangle.getPosition().y;
		int integerVelY;
		integerVelY = velocity.x;
		if ((posY - integerVelY) % CONVERTER < CONVERTER / 2)
			newPosition.y = posY + multiplierY * (integerVelY % CONVERTER);
		else
			newPosition.y = posY - (CONVERTER - (CONVERTER - integerVelY) % CONVERTER);


		newPosition.x = rectangle.getPosition().x;
		velocity.y = 0;
	}
	setPosition(newPosition.x, newPosition.y);
	*/

	if (horizontal)
		velocity.x = 0;
	else
		velocity.y = 0;


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
void GameObject::setTexture(std::string fileName)
{
	if (!texture.loadFromFile(fileName))
		std::cout << fileName << std::endl;
	else
	{
		setTexture();
	}
}
void GameObject::setTexture(sf::Texture set)
{
	texture = set;
	setTexture();
}
void GameObject::setTexture()
{
	rectangle.setTexture(&texture);
	sf::Vector2f vec;
	vec.x = texture.getSize().x * SCREEN_MULTIPLIER;
	vec.y = texture.getSize().y * SCREEN_MULTIPLIER;
	rectangle.setSize(vec);
}
void GameObject::setPosition(float x, float y)
{
	rectangle.setPosition(x, y);
}
void GameObject::setGameDataPTR(GameData *set)
{
	gameData = set;
}

//Clock
void GameObject::setTimeLimit(sf::Time set)
{
	timeLimit = set;
}
void GameObject::startClock(sf::Time set)
{
	timeLimit = set;
	trackingTime = true;
	clock.restart();
}
void GameObject::startClock()
{
	trackingTime = true;
	clock.restart();
}
sf::Time GameObject::stopClock()
{
	trackingTime = false;
	timeElapsed = clock.getElapsedTime();
	return timeElapsed;
}

//Pedometer
void GameObject::setPedometerLimit(float set)
{
	distanceLimit = set;
}
void GameObject::startPedometer(float set)
{
	distanceLimit = set;
	trackingDistance = true;
	pedometer = 0;
}
void GameObject::startPedometer()
{
	trackingDistance = true;
	pedometer = 0;
}
double GameObject::stopPedometer()
{
	trackingDistance = false;
	distanceElapsed = pedometer;
	return pedometer;
}

bool GameObject::offTop()
{
	if (rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height <= 0)
		return true;
	return false;
}
bool GameObject::offBottom()
{
	if (rectangle.getGlobalBounds().top >= window->getSize().y)
		return true;
	return false;
}

void GameObject::changePositionVertical(float distance)
{
	setPosition(rectangle.getPosition().x, rectangle.getPosition().y + distance);
}