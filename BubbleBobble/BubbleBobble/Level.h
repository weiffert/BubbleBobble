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
	void collision(GameObject *);
	void update();
	void timeLimitPassed();
	void distanceLimitPassed();
	void levelTransition();
	void levelStart();
	void levelPlay();
	void levelEnd();
	void death();
	void bitmapMaker();

private:
	//MAKE SURE THIS IS CORRECT!!!!
	const int BITMAP_WIDTH = 32;
	const int BITMAP_HEIGHT = 26;
	int bitmap[32][26];
	int monsterSpawns[32][26];
	void enemyCheck();
	void startLevel();
};

