#pragma once
#include <string>
#include <vector>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

class GameObject
{
public:
	GameObject();
	~GameObject();
	//Game Logic
	void collision(GameObject);
	void time();
	void distance();

	//Updates every step.
	virtual void update();

	//Specific event type functions.
	virtual void collided();
	virtual void timeLimitPassed();
	virtual void distanceLimitPassed();
	virtual void death();

	std::string getName();
	sf::Time getTimeElapsed();
	float getDistanceElapsed();
	sf::Vector2f getVelocity();
	//need to be added
	sf::RectangleShape getRectangle();
	sf::Texture getTexture();

	void setName(std::string);
	void setTimeLimit(sf::Time);
	void setPedometerLimit(float);
	void setVelocity(sf::Vector2f);

	void startClock();
	void startPedometer();
	double stopClock();
	double stopPedometer();

protected:
	sf::Vector2f velocity;

	sf::Clock clock;
	sf::Time timeElapsed;
	sf::Time timeLimit;
	bool trackingTime;

	float pedometer;
	float distanceElapsed;
	float distanceLimit;
	bool trackingDistance;

	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::string name;
	std::vector<double> data;
};

