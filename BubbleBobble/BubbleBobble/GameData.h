#pragma once
#include <vector>
#include "GameObject.h"

class GameObject;

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
	bool exist(unsigned int);
	void clear(unsigned int);

private:
	void remove(unsigned int, GameObject *);
	void remove(unsigned int, unsigned int);
	void remove(unsigned int);
	std::vector<std::vector<GameObject *>> gameObjects;
	std::vector<std::vector<GameObject *>> killList;
};

