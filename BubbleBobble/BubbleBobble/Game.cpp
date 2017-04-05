#include "stdafx.h"
#include "Game.h"
#include <iostream>


Game::Game()
{
    FPS_m = 60;
    screenDimensions.x = 256 * 4;
    screenDimensions.y = 224 * 4;
	window = new sf::RenderWindow();
    window->create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Bubble Bobble");
	//view.reset(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(256, 224)));
	//view.setViewport(sf::FloatRect(0.f, 0.f, .25f, .25f));
	//window.setView(view);
    window->setFramerateLimit(FPS_m);
    stateManager.push_State(new SplashScreenState(window));
}

/*
Game::Game(int FPS = 60, int screenHeight = 256, int screenWidth = 224)
{
    FPS_m = FPS;
    screenDimensions.x = screenHeight;
    screenDimensions.y = screenWidth;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Bubble Bobble");
    //window.setFramerateLimit(FPS_m);
}
*/

Game::~Game()
{
	std::cout << "Deconstructing Game" << std::endl;
	if (window != nullptr)
	{
		std::cout << "Deleting Window" << std::endl;
		delete window;
	}
}

void Game::loop()
{

    while(window->isOpen())
    {
        //Checks for any events that occur while the window is open
        sf::Event event;
		while (window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
				window->close();
            stateManager.processEvents(window, event);
        }
        stateManager.process();
		window->clear();
        stateManager.draw();
		window->display();
    }
}