#include "stdafx.h"
#include "StateManager.h"

StateManager::StateManager()
{
    //ctor
}


StateManager::~StateManager()
{
    //dtor
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
   //this->unload();
   states.back()->unload();
   delete states.back();
}

void StateManager::unload()
{
    states.back()->unload();
}


