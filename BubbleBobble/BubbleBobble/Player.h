#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();
	virtual void levelTransition();
	virtual void death();
};

