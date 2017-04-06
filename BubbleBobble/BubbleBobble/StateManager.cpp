#include "stdafx.h"
#include "StateManager.h"
#include <iostream>

StateManager::StateManager()
{

}


StateManager::~StateManager()
{
	std::cout << "Deconstructing StateManager" << std::endl;
	while (!states.empty())
	{
		delete states.at(0);
		states.erase(states.begin());
	}
}

void StateManager::processEvents(sf::RenderWindow *window, sf::Event event)
{
    states.back()->processEvents(event);
    if(states.back()->switchTrue())
    {
        if(states.back()->nextState() == "SplashScreenState")
        {
            this->pop_State();
            this->push_State(new SplashScreenState(window));
        }
        else if(states.back()->nextState() == "MenuState")
        {
            this->pop_State();
            this->push_State(new MenuState(window));
        }
        else if(states.back()->nextState() == "GameState")
        {
            this->pop_State();
            this->push_State(new GameState(window));
        }
    }
	else if (states.back()->pause())
	{
		if (states.back()->nextState() == "SplashScreenState")
		{
			this->pop_State();
			this->push_State(new SplashScreenState(window));
		}
		else if (states.back()->nextState() == "MenuState")
		{
			this->pop_State();
			this->push_State(new MenuState(window));
		}
		else if (states.back()->nextState() == "GameState")
		{
			this->pop_State();
			this->push_State(new GameState(window));
		}
	}
}

void StateManager::process()
{
    states.back()->process();
}

void StateManager::draw()
{
    states.back()->draw();
}

void StateManager::push_State(BaseState *newState )
{
    states.push_back(newState);
}

void StateManager::pop_State()
{
	delete states.back();
	states.back()->unload();
	states.erase(states.begin() + states.size() - 1);
}

void StateManager::unload()
{
    states.back()->unload();
}


