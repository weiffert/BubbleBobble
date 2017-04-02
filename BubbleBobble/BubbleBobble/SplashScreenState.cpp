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
	//GameData Drawing.
}

//Does nothing in SplashScreenState
void SplashScreenState::pause()
{

}