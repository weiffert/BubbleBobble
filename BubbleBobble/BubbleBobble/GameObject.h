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
	virtual void collision(GameObject *);
	void time();
	void distance();
	virtual void render();

	//Updates every step.
	virtual bool update();
	virtual void updateVelocity();

	//Specific event type functions.
	virtual void collided();
	virtual void timeLimitPassed();
	virtual void distanceLimitPassed();
	virtual void death();
	virtual void levelTransition();

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
	void setVelocity(float, float);
	void velocityToNextGridLine(bool);
	void setRenderWindow(sf::RenderWindow *);
	void setAnimation(std::string);
	void setPosition(float, float);

	void startClock();
	void startPedometer();
	sf::Time stopClock();
	double stopPedometer();

	bool offTop();
	bool offBottom();

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
	bool life;
	sf::RenderWindow *window;
};

