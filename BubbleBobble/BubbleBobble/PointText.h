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
	PointText(std::string, GameObject *);
	~PointText();
	virtual void death();
};

