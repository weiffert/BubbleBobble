#pragma once
#include <vector>
#include "GameObject.h"

class GameData
{
public:
	GameData();
	~GameData();
	void kill();
	std::vector<std::vector<GameObject *>> getAll();
	std::vector<GameObject *> getList(unsigned int);
	void add(unsigned int, GameObject *);
	void addToKillList(unsigned int, GameObject *);
	void remove(unsigned int, GameObject *);
	void remove(unsigned int, unsigned int);
	void clear(unsigned int);
	bool exist(unsigned int);

private:
	std::vector<std::vector<GameObject *>> gameObjects;
	std::vector<std::vector<GameObject *>> killList;
};
