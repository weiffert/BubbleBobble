#include "stdafx.h"
#include "SplashScreenState.h"

SplashScreenState::SplashScreenState()
{
	//Pushback any gameobjects you want
	//in here for the splash screen state

	//This bool keeps the statemanager
	//from switching to the menustate
    stateSwitch = false;
    c1.restart();
}

SplashScreenState::~SplashScreenState()
{
    //dtor
}

void SplashScreenState::processEvents(sf::RenderWindow &window, sf::Event event)
{
	//If you press space switch to the menu state
    inputManager.update(event);
    if(inputManager.keyPressed(sf::Keyboard::Space))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
}

void SplashScreenState::process(sf::RenderWindow &window)
{

}

void SplashScreenState::draw(sf::RenderWindow &window)
{
    window.setView(centered);
	for (int i = 0; i < objectVector.size(); i++)
	{
		for(int n = 0; n < objectVector.at(i).size(); n++)
			window.draw(objectVector.at(i).at(n)->render());
	}
}

//Does nothing in SplashScreenState
void SplashScreenState::pause()
{

}