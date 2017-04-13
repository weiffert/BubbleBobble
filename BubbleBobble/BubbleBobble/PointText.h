#pragma once
#include "GameObject.h"

/*
For the text that appears above an object when collected.
*/

class PointText : 
	public GameObject
{
public:
	PointText();
	PointText(sf::RenderWindow *, GameData *, GameObject *, unsigned int, bool);
	~PointText();
	void death();
};

