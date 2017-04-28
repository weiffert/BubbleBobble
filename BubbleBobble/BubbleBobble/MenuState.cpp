#include "stdafx.h"
#include "MenuState.h"
#include <iostream>

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

	menuTexture.loadFromFile("../textures/Menu/1pStart.png");
	menuScreen.setSize(sf::Vector2f(window->getSize()));
	menuScreen.setTexture(&menuTexture);
}

MenuState::~MenuState()
{
    //dtor
	std::cout << "Deconstructing menu screen" << std::endl;
}

void MenuState::processEvents(sf::Event event)
{
	enum menuItems {onePlay, twoPlay, oneContinue, twoContinue};

	//Change state to GameState when an option is chosen
    inputManager.update(event);
    
	//menu controls up & down to select
	if (inputManager.keyPressed(sf::Keyboard::Down))
	{
		if(selection < 3)
			selection++;
	}
	else if (inputManager.keyPressed(sf::Keyboard::Up))
	{
		if (selection > 0)
			selection--;
	}

	//load & apply textures
	switch (selection)
	{
	case onePlay:
		menuTexture.loadFromFile("../textures/Menu/1pStart.png");
		menuScreen.setTexture(&menuTexture);
		break;
	case twoPlay:
		menuTexture.loadFromFile("../textures/Menu/2pStart.png");
		menuScreen.setTexture(&menuTexture);
		break;
	case oneContinue:
		menuTexture.loadFromFile("../textures/Menu/1pContinue.png");
		menuScreen.setTexture(&menuTexture);
		break;
	case twoContinue:
		menuTexture.loadFromFile("../textures/menu/2pContinue.png");
		menuScreen.setTexture(&menuTexture);
		break;
	}

	if (inputManager.keyPressed(sf::Keyboard::Return))
	{
		stateSwitch = true;
		nextStateS = "GameState";
	}
}


void MenuState::draw()
{
	window->draw(menuScreen);
}