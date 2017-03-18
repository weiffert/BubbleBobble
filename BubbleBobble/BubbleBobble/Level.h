#pragma once
#include "GameObject.h"
#include <string>

class Level :
	public GameObject
{
public:
	Level();
	Level(std::string);
	~Level();
	virtual void collision(GameObject *);
	void bitmapMaker();

private:
	const int BITMAP_WIDTH = 32;
	const int BITMAP_HEIGHT = 28;
	int bitmap[32][28];
};

