#include "stdafx.h"
#include "Game.h"
#include <iostream>


Game::Game()
{
    FPS_m = 60;
    screenDimensions.x = 256 * 3;
    screenDimensions.y = 208 * 3;
	window = new sf::RenderWindow();
    window->create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Bubble Bobble");
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
		window = nullptr;
	}
}


void Game::loop()
{
	//sf::Clock clock;
    while(window->isOpen())
    {
		//clock.restart();
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

		//sf::Time time = clock.getElapsedTime();
		//std::cout << "Elaspsed time - " << time.asSeconds() << std::endl;
    }
}