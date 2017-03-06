#pragma once
#include <string>
#include <vector>

class GameObject
{
public:
	GameObject();
	~GameObject();
	//Game Logic
	void collision(GameObject);
	//Updates every step.
	virtual void update();
	//Specific event type functions.
	virtual void collide();
	virtual void death();
	virtual void startTimer();
	virtual void startPedometer();
	virtual void stopTimer();
	virtual void stopPedometer();

protected:
	double velocityX;
	double velocityY;
	double timer;
	double pedometer;
	std::string name;
	std::vector<double> data;
};

