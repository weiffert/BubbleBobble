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
	//Constructors.
	GameObject();
	GameObject(std::string, sf::RenderWindow *, GameData *);
	~GameObject();

	//Game Logic
	//Updates every step. Determines whether levelPlay or levelTransition is called.
	virtual void update();

	//Controls most of the object behavior.
	virtual void levelPlay();
	virtual void levelTransition();

	//Performs changes to the game object based on level changing.
	virtual void levelStart();
	virtual void levelEnd();

	//Collision for basic collision.
	virtual void collision(GameObject *);

	//controls what collides with what. 
	virtual void collideWith();

	//Reaction to collision.
	virtual void collided(GameObject *);

	//Function for general time testing.
	void time();
	void setTimeLimit(sf::Time);
	void startClock(sf::Time);
	void startClock();
	sf::Time stopClock();
	virtual void timeLimitPassed();
	sf::Time getTimeElapsed();

	//Function for general distance (pedometer) testing.
	void distance();
	void setPedometerLimit(float);
	void startPedometer(float);
	void startPedometer();
	double stopPedometer();
	virtual void distanceLimitPassed();
	float getDistanceElapsed();

	//Positioning editing.
	void moveLeft();
	void moveRight();
	void stopHorizontalVelocity();
	void stopVerticalVelocity();
	void reverseDirectionHorizontal();
	void reverseDirectionVertical();
	void jump();
	int getVerticalAcceleration();
	void changePositionVertical(float);
	void setPosition(float, float);

	//Get the direction the object is facing.
	int getDirection();

	//Testing if off screen.
	bool offTop();
	bool offBottom();

	//Function for general rendering.
	virtual void render();

	//Kill the object.
	virtual void death();

	//Perform gravity functions.
	void gravity();

	//General value getting and setting.
	void setName(std::string);
	std::string getName();

	void setVelocity(sf::Vector2f);
	void setVelocity(float, float);
	void velocityToNextGridLine(bool);
	sf::Vector2f getVelocity();

	void setTexture(sf::Texture);
	void setTexture(std::string);
	void setTexture();
	sf::Texture getTexture();

	sf::RectangleShape getRectangle();

	void setAnimation(std::string);

	bool isTransitioningLevels();

	bool isFriendly();

	void setRenderWindow(sf::RenderWindow *);
	void setGameDataPTR(GameData *);

	

protected:
	const int SCREEN_MULTIPLIER = 3;
	const int BITMAP_CONVERTER = SCREEN_MULTIPLIER * 8;

	std::string name;
	sf::RenderWindow *window;
	GameData *gameData;

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

	int verticalAcceleration;
	int direction;

	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::vector<Animation> animations;
	bool life;
};

