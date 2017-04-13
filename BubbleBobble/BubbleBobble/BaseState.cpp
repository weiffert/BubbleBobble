#include "stdafx.h"
#include "BaseState.h"
#include <iostream>

BaseState::BaseState()
{
	window = nullptr;
	gameData = nullptr;
}


BaseState::BaseState(sf::RenderWindow* win)
{
	window = win;
	gameData = nullptr;
}

BaseState::~BaseState()
{
	std::cout << "Deconstructing BaseState" << std::endl;
	if (gameData != nullptr)
	{
		std::cout << "Deleting GameData" << std::endl;
		delete gameData;
		gameData = nullptr;
	}
	//Window is not deleted here. It is deleted in Game.
}

bool BaseState::pause()
{
	if (pause_m)
		return true;
	else
		return false;
}

void BaseState::processEvents(sf::Event event)
{
}

void BaseState::process()
{
}

void BaseState::draw()
{
}

bool BaseState::switchTrue()
{
    if(stateSwitch)
        return true;
    else
        return false;
}

std::string BaseState::nextState()
{
    return nextStateS;
}

GameData * BaseState::getGameDataPTR()
{
	return gameData;
}
