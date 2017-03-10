#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}


std::vector<std::vector<GameObject *>> GameManager::getObjects()
{
	return objects;
}

std::vector<GameObject *> GameManager::getListObjects(std::string type)
{
	if (type == "level")
		return objects.at(0);
	else if (type == "player")
		return objects.at(1);
	else if (type == "pickup")
		return objects.at(2);
	else if (type == "monsters")
		return objects.at(3);
	else
		return objects.at(3);
}

void GameManager::loop()
{
	for (int i = 0)
}