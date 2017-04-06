#pragma once
#include <string>
#include <vector>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "GameData.h"

//Will: I don't know why this removes some errors, but it does.
class GameData;

class GameObject
{
public:
	GameObject();
	GameObject(std::string);
	~GameObject();
	void initialize(sf::RenderWindow *, GameData *);
	//Game Logic
	virtual void collision(GameObject *);
	void time();
	void distance();
	virtual void render();

	//Updates every step.
	virtual void update();
	//controls what collides with what. Level collision is NOT handled in here. That is done in update velocity. 
	//What object that has precedence over what it is colliding with calls the collision function.
	virtual void collideWith();

	//Specific event type functions.
	virtual void collided(GameObject *);
	virtual void timeLimitPassed();
	virtual void distanceLimitPassed();
	virtual void death();
	//Performs changes to the game object based on level changing.
	virtual void levelStart();
	virtual void levelEnd();
	//Controls the behavior.
	virtual void levelPlay();
	virtual void levelTransition();

	std::string getName();
	sf::Time getTimeElapsed();
	float getDistanceElapsed();
	sf::Vector2f getVelocity();
	sf::RectangleShape getRectangle();
	sf::Texture getTexture();
	bool isTransitioningLevels();
	bool isFriendly();

	void setName(std::string);
	void setTimeLimit(sf::Time);
	void setPedometerLimit(float);
	void setVelocity(sf::Vector2f);
	void setVelocity(float, float);
	void velocityToNextGridLine(bool);
	void setRenderWindow(sf::RenderWindow *);
	void setAnimation(std::string); 
	void setTexture(sf::Texture);
	void setTexture(std::string);
	void setTexture();
	void setPosition(float, float);
	void setGameDataPTR(GameData *);

	void startClock();
	void startPedometer();
	sf::Time stopClock();
	double stopPedometer();

	bool offTop();
	bool offBottom();

protected:
	std::string name;
	bool friendly;
	bool transition;

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
	std::vector<double> data;
	bool life;
	sf::RenderWindow *window;
	GameData *gameData;
};

