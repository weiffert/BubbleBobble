#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include <string>

class Level :
	public GameObject
{
public:
	Level();
	Level(std::string);
	~Level();
	virtual void collision(GameObject *);
	virtual void update();
	virtual void timeLimitPassed();
	virtual void distanceLimitPassed();
	void bitmapMaker();

private:
	const int BITMAP_WIDTH = 32;
	const int BITMAP_HEIGHT = 28;
	int bitmap[32][28];
	void enemyCheck();
	void levelTransition();
};

