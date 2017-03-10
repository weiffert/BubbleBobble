#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	std::vector<std::vector<GameObject *>> getObjects();
	std::vector<GameObject *> getListObjects(std::string);
	void loop();

private:
	//1: level. 2: player. 3: pickup. 4: monsters.
	std::vector<std::vector<GameObject *>> objects;
};

