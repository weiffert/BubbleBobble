#include "stdafx.h"
#include "SplashScreenState.h"

SplashScreenState::SplashScreenState()
{
	//Pushback any gameobjects you want
	//in here for the splash screen state

	//This bool keeps the statemanager
	//from switching to the menustate
	stateSwitch = false;
	window = nullptr;
	c1.restart();
}


SplashScreenState::SplashScreenState(sf::RenderWindow *win)
{
	//Pushback any gameobjects you want
	//in here for the splash screen state

	//This bool keeps the statemanager
	//from switching to the menustate
	stateSwitch = false;
	window = win;
	c1.restart();
}

SplashScreenState::~SplashScreenState()
{
    //dtor
}

void SplashScreenState::processEvents(sf::Event event)
{
	//If you press space switch to the menu state
    inputManager.update(event);
    if(inputManager.keyPressed(sf::Keyboard::Space))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
}

void SplashScreenState::process()
{

}

void SplashScreenState::draw()
{
    //window->setView(centered);
	//GameData Drawing.
}

//Does nothing in SplashScreenState
void SplashScreenState::pause()
{

}