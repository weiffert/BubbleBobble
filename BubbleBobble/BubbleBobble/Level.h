#pragma once
#include "GameObject.h"
class Level :
	public GameObject
{
public:
	Level();
	~Level();
	virtual void collision(GameObject *);
	void bitmapMaker();

private:
	int bitmap[32][28];
};

