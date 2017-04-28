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
	verticalAcceleration = 0;
	direction = 1;
	trackingDistance = false;
	life = true;
	transition = false;
	friendly = true;

	setLives(1);
}

GameObject::GameObject(std::string set, sf::RenderWindow *win, GameData *data)
{
	std::cout << "Constructing GameObject" << std::endl;
	gameData = data;
	window = win;

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
	verticalAcceleration = 0;
	direction = 1;
	trackingDistance = false;
	life = true;
	transition = false;
	friendly = true;

	setLives(1);
}

GameObject::~GameObject()
{
	std::cout << "Deconstructing GameObject " << name << std::endl;
}


//Game Logic
//Updates every step. Determines whether levelPlay or levelTransition is called.
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


//Controls most of the object behavior.
void GameObject::levelPlay()
{
	//move.
	gravity();
	collideWith();
	rectangle.move(velocity);
}

void GameObject::levelTransition()
{
	//Do nothing.
}


//Performs changes to the game object based on level changing.
void GameObject::levelEnd()
{
	transition = true;
}

void GameObject::levelStart()
{
	transition = false;
	gravity();
}


//Collision for basic collision.
void GameObject::collision(GameObject *other)
{
	if (rectangle.getGlobalBounds().intersects(other->getRectangle().getGlobalBounds()))
	{
		collided(other);
		other->collided(this);
	}
}


//controls what collides with what. 
void GameObject::collideWith()
{

}


//Reaction to collision.
void GameObject::collided(GameObject *)
{
	
}


//Function for general time testing.
void GameObject::time()
{
	if (trackingTime && clock.getElapsedTime() >= timeLimit)
	{
		stopClock();
		timeLimitPassed();
	}
}

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

void GameObject::timeLimitPassed()
{
	death();
}

sf::Time GameObject::getTimeElapsed()
{
	if (trackingTime)
		return clock.getElapsedTime();
	return timeElapsed;
}


//Function for general distance (pedometer) testing.
void GameObject::distance()
{
	if (trackingDistance)
	{
		//Increments the pedometer by the hypotnuse of every move.
		pedometer += std::abs(std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y));

		if (pedometer >= distanceLimit)
		{
			stopPedometer();
			distanceLimitPassed();
		}
	}
}

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

void GameObject::distanceLimitPassed()
{
	death();
}

float GameObject::getDistanceElapsed()
{
	return pedometer;
}


//Positioning editing.
void GameObject::moveLeft()
{
	setVelocity(-1 * SCREEN_MULTIPLIER, velocity.y);
	//move towards negative x
	direction = -1;
	//flip the texture if needed
	flipTexture();
}

void GameObject::moveRight()
{
	setVelocity(SCREEN_MULTIPLIER, velocity.y);
	//move towards positive x
	direction = 1;
	//flip the texture if needed
	flipTexture();
}

void GameObject::stopHorizontalVelocity()
{
	setVelocity(0, velocity.y);
}

void GameObject::stopVerticalVelocity()
{
	setVelocity(getVelocity().x, 0);
}

void GameObject::reverseDirectionHorizontal()
{
	velocity.x *= -1;
	//set texture to oppsite direction
	direction *= -1;
	//flip the texture if necessary
	flipTexture();
}

void GameObject::reverseDirectionVertical()
{
	velocity.y *= -1;
}

void GameObject::jump()
{
	verticalAcceleration = -5 * 8;
}

//Perform gravity functions.
void GameObject::gravity()
{
	if (verticalAcceleration < 0)
		velocity.y = -1 * SCREEN_MULTIPLIER;
	else
		velocity.y = 1 * SCREEN_MULTIPLIER;

	verticalAcceleration++;
}

int GameObject::getVerticalAcceleration()
{
	return verticalAcceleration;
}

void GameObject::changePositionVertical(float distance)
{
	setPosition(rectangle.getPosition().x, rectangle.getPosition().y + distance);
}

void GameObject::setPosition(float x, float y)
{
	rectangle.setPosition(x, y);
}


//Get the direction the object is facing.
int GameObject::getDirection()
{
	return direction;
}


//Testing if off screen.
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


//Function for general rendering.
void GameObject::render()
{
	window->draw(rectangle);
}


//Kill the object.
void GameObject::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}


//General value getting and setting.
std::string GameObject::getName()
{
	return name;
}

void GameObject::setName(std::string set)
{
	name = set;
}


sf::Vector2f GameObject::getVelocity()
{
	return velocity;
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
	sf::Vector2f newPosition, position;
	position.x = rectangle.getGlobalBounds().left;
	position.y = rectangle.getGlobalBounds().top;
	newPosition.x = position.x;
	newPosition.y = position.y;

	if (horizontal)
	{
		if (velocity.x >= 0)
			newPosition.x = std::floor((position.x + velocity.x) / BITMAP_CONVERTER) * BITMAP_CONVERTER - 1;
		else
			newPosition.x = std::floor((position.x + velocity.x) / BITMAP_CONVERTER + 1) * BITMAP_CONVERTER;

		velocity.x = 0;
	}
	else
	{
		newPosition.y = std::floor((position.y + velocity.y) / BITMAP_CONVERTER - 1) * BITMAP_CONVERTER + BITMAP_CONVERTER - 1;
		verticalAcceleration = window->getSize().y;
		velocity.y = 0;
	}

	rectangle.setPosition(newPosition.x, newPosition.y);
}


void GameObject::setAnimation(std::string type)
{
	if (type == "")
	{
		animations.push_back(Animation(&texture, sf::Vector2u(1, 0), 0, 0));
	}
}

void GameObject::setTexture(std::string fileName)
{
	if (!texture.loadFromFile(fileName))
		std::cout << fileName << std::endl;
	else
	{
		setTexture();
		textureSource = fileName;
	}
}

void GameObject::setTexture(sf::Texture set)
{
	texture = set;
	setTexture();
}

//Applies the current texture.
void GameObject::setTexture()
{
	rectangle.setTexture(&texture);
	//Sets the rectangle to be the texture's size.
	sf::Vector2f vec;
	vec.x = texture.getSize().x * SCREEN_MULTIPLIER;
	vec.y = texture.getSize().y * SCREEN_MULTIPLIER;
	rectangle.setSize(vec);
}

sf::Texture GameObject::getTexture()
{
	return texture;
}


sf::RectangleShape GameObject::getRectangle()
{
	return rectangle;
}


bool GameObject::isTransitioningLevels()
{
	return transition;
}


bool GameObject::isFriendly()
{
	return friendly;
}


void GameObject::setRenderWindow(sf::RenderWindow *set)
{
	window = set;
}


void GameObject::setGameDataPTR(GameData *set)
{
	gameData = set;
}

void GameObject::flipTexture()
{
	if (direction == -1)
	{
		texture.loadFromFile(textureSource);
	}
	else
	{
		sf::Image newTexture;
		newTexture.loadFromFile(textureSource);
		newTexture.flipHorizontally();
		texture.loadFromImage(newTexture);
	}
}


void GameObject::setLives(unsigned int lives)
{
	livesRemaining = lives;
}


int GameObject::getLivesRemaining()
{
	return livesRemaining;
}


void GameObject::fireProjectile()
{
}