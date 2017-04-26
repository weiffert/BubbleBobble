#include "stdafx.h"
#include "SplashScreenState.h"
#include <iostream>

SplashScreenState::SplashScreenState()
{
	//Pushback any gameobjects you want
	//in here for the splash screen state

	//This bool keeps the statemanager
	//from switching to the menustate
	stateSwitch = false;
	window = nullptr;
}


SplashScreenState::SplashScreenState(sf::RenderWindow *win)
{
	//Pushback any gameobjects you want
	//in here for the splash screen state
	

	//This bool keeps the statemanager
	//from switching to the menustate
	stateSwitch = false;
	window = win;

	titleScreenTexture.loadFromFile("../textures/titleScreen.png");
	titleScreen.setSize(sf::Vector2f(window->getSize()));
	titleScreen.setTexture(&titleScreenTexture);
}


SplashScreenState::~SplashScreenState()
{
    //dtor
	std::cout << "Deconstructing title screen" << std::endl;
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


void SplashScreenState::draw()
{
    //window->setView(centered);
	//GameData Drawing.
	window->draw(titleScreen);
}