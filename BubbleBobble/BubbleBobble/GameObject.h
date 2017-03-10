#pragma once
#include <string>
#include <vector>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "Animation.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	//Game Logic
	void collision(GameObject);
	void time();
	void distance();
	void render();

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
	sf::RectangleShape getRectangle();
	sf::Texture getTexture();

	void setName(std::string);
	void setTimeLimit(sf::Time);
	void setPedometerLimit(float);
	void setVelocity(sf::Vector2f);
	void setRenderWindow(sf::RenderWindow *);
	void setAnimation(std::string);

	void startClock();
	void startPedometer();
	double stopClock();
	double stopPedometer();

protected:
	sf::Vector2f velocity;

	//Clock variables.
	sf::Clock clock;
	sf::Time timeElapsed;
	sf::Time timeLimit;
	bool trackingTime;

	//Distance variables.
	float pedometer;
	float distanceElapsed;
	float distanceLimit;
	bool trackingDistance;

	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::vector<Animation> animations;
	std::string name;
	std::vector<double> data;
	sf::RenderWindow *window;
};

