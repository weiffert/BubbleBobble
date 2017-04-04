#include "stdafx.h"
#include "BaseState.h"

BaseState::BaseState()
{
	folder = "empty";
	window = nullptr;
}


BaseState::BaseState(sf::RenderWindow* win)
{
	folder = "empty";
	window = win;
}

void BaseState::pause()
{
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

void BaseState::unload()
{
    //files.unload();
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

BaseState::~BaseState()
{
    //dtor
}
