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
	virtual bool update();
	virtual void timeLimitPassed();
	virtual void distanceLimitPassed();
	virtual void levelTransition();
	virtual void death();
	void bitmapMaker();

private:
	const int BITMAP_WIDTH = 32;
	const int BITMAP_HEIGHT = 28;
	int bitmap[32][28];
	void enemyCheck();
	void startLevel();
};

