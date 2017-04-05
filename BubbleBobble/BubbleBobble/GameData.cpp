#include "stdafx.h"
#include "GameData.h"
#include <iostream>


GameData::GameData()
{
	std::vector<GameObject *> newList;
	for (int i = 0; i < 6; i++)
	{
		gameObjects.push_back(newList);
		killList.push_back(newList);
	}
}


GameData::~GameData()
{
	std::cout << "Deconstructing GameData" << std::endl;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		clear(i);
	}
}


//Precondition: everything is properly sorted;
void GameData::kill()
{
	for(int i = 0; i < 6; i++)
	{
		int increment1 = 0;
		int increment2 = 0;
		while (!killList.at(i).empty())
		{
			if (killList.at(i).at(increment1) == gameObjects.at(i).at(increment2))
			{
				GameObject *temp = killList.at(i).at(0);
				killList.at(i).erase(killList.at(i).begin());
				remove(i, temp);
				increment1++;
			}
			increment2++;
		}
	}
}


std::vector<std::vector<GameObject *>> GameData::getAll()
{
	return gameObjects;
}


std::vector<GameObject *> GameData::getList(unsigned int index)
{
	if (index < gameObjects.size())
	{
		return gameObjects.at(index);
	}
	else
	{
		std::cout << "Out of bounds error";
		return gameObjects.at(0);
	}
}


void GameData::add(unsigned int index, GameObject *other)
{
	if (index < gameObjects.size())
	{
		gameObjects.at(index).push_back(other);
	}
	else
	{
		std::cout << "Out of bounds. Pushing to new vector." << std::endl;
		std::vector<GameObject*> newInformation;
		newInformation.push_back(other);
		gameObjects.push_back(newInformation);
	}
}


void GameData::addToKillList(unsigned int index, GameObject *other)
{
	if (index < killList.size())
	{
		killList.at(index).push_back(other);
	}
	else
	{
		std::cout << "Out of bounds. Pushing to new vector." << std::endl;
		std::vector<GameObject*> newInformation;
		newInformation.push_back(other);
		killList.push_back(newInformation);
	}
}


void GameData::remove(unsigned int index, GameObject *other)
{
	if (index < gameObjects.size())
	{
		int size = gameObjects.at(index).size();
		int increment = 0;

		while (gameObjects.at(index).at(increment) != other && increment < size)
		{
			increment++;
		}

		if (gameObjects.at(index).at(increment) == other)
		{
			delete gameObjects.at(index).at(increment);
			gameObjects.at(index).erase(gameObjects.at(index).begin() + increment);
		}
		else
		{
			std::cout << "Failed to delete anything" << std::endl;
		}
	}
	else
	{
		std::cout << "Out of bounds. Searching whole vector of vectors." << std::endl;

		int increment1, increment2;
		increment1 = 0;
		increment2 = 0;
		while (gameObjects.at(increment1).at(increment2) != other && increment1 < gameObjects.size())
		{
			while (gameObjects.at(increment1).at(increment2) != other && increment2 < gameObjects.at(increment1).size())
			{
				increment2++;
			}
			increment1++;
		}

		if (gameObjects.at(increment1).at(increment2) == other)
		{
			delete gameObjects.at(increment1).at(increment2);
			gameObjects.at(increment1).erase(gameObjects.at(increment1).begin() + increment2);
		}
		else
		{
			std::cout << "Failed to delete anything" << std::endl;
		}
	}
}


void GameData::remove(unsigned int index1, unsigned int index2)
{
	bool failed = true;
	if (index1 < gameObjects.size())
	{
		if (index2 < gameObjects.at(index1).size())
		{
			failed = false;
			delete gameObjects.at(index1).at(index2);
			gameObjects.at(index1).erase(gameObjects.at(index1).begin() + index2);
		}
	}
	if (failed)
	{
		std::cout << "Failed to delete anything" << std::endl;
	}
}


void GameData::clear(unsigned int index)
{
	if (index < gameObjects.size())
	{
		while (!gameObjects.at(index).empty())
		{
			delete gameObjects.at(index).at(0);
			gameObjects.at(index).erase(gameObjects.at(index).begin());
		}
	}
	else
	{
		std::cout << "Out of bounds. Failed to delete anything" << std::endl;
	}
}


bool GameData::exist(unsigned int index)
{
	if (index < gameObjects.size())
	{
		return (!gameObjects.at(index).empty());
	}
	else
	{
		std::cout << "Out of bounds. Returning false." << std::endl;
		return false;
	}
}