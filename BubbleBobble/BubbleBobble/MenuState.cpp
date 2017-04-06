#include "stdafx.h"
#include "MenuState.h"

MenuState::MenuState()
{
	//Push back game objects you want 
	//initially for the state here

	//Prevents stateManager from
	//switching the state
	stateSwitch = false;
	window = nullptr;
}

MenuState::MenuState(sf::RenderWindow *win)
{
	//Push back game objects you want 
	//initially for the state here

	//Prevents stateManager from
	//switching the state
	stateSwitch = false;
	window = win;
}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::pause()
{
}

void MenuState::processEvents(sf::Event event)
{
	//Change state to GameState when the escape key is pressed
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "GameState";
    }

}

void MenuState::process()
{
}

void MenuState::draw()
{
	window->setView(centered);
	//gameData stuff.
}
