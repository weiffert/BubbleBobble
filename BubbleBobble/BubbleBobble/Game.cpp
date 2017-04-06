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

	/*
	sf::View view(sf::FloatRect(0, 0, 256, 224));
	view.setSize(256, 224);
	view.setCenter(256 / 2, 224 / 2);
	view.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
	view.setRotation(45);
	window->setView(view);
	*/

    window->setFramerateLimit(FPS_m);
    stateManager.push_State(new SplashScreenState(window));
}

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