#include "stdafx.h"
#include "MenuState.h"

MenuState::MenuState()
{
    //Push back game objects you want 
	//initially for the state here

	//Prevents stateManager from
	//switching the state
    stateSwitch = false;

}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::pause()
{
}

void MenuState::processEvents(sf::RenderWindow &window, sf::Event event)
{
	//Change state to GameState when the escape key is pressed
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "GameState";
    }

}

void MenuState::process(sf::RenderWindow &window)
{
}

void MenuState::draw(sf::RenderWindow &window)
{
	window.setView(centered);
	for (int i = 0; i < objectVector.size(); i++)
	{
		for (int n = 0; n < objectVector.at(i).size(); n++)
			window.draw(objectVector.at(i).at(n)->render());
	}
}
