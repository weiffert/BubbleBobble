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
	PointText(GameObject *, unsigned int, bool);
	~PointText();
	virtual void death();
};

