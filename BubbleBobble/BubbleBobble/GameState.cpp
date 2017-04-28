#include "stdafx.h"
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <iostream>


GameState::GameState()
{
	window = nullptr;
	initialize(false);
}


GameState::GameState(sf::RenderWindow *win)
{
	window = win;
	initialize(false);
}


GameState::GameState(sf::RenderWindow *win, bool twoPlayer)
{
	window = win;
	initialize(twoPlayer);
}


GameState::~GameState()
{
	std::cout << "Deconstructing GameState" << std::endl;
	if (gameData != nullptr)
	{
		std::cout << "Deleting GameData" << std::endl;
		delete gameData;
		gameData = nullptr;
	}
}


void GameState::initialize(bool twoPlayer)
{
	//create the level.
	gameData = new GameData();
	GameObject *level = new Level("Level0", window, gameData);
	gameData->add(0, level);

	//create the players.
	GameObject *player1 = new Player("Player1", window, gameData);
	gameData->add(1, player1);
	if (twoPlayer)
	{
		GameObject *player2 = new Player("Player2", window, gameData);
		gameData->add(1, player2);
	}
}


void GameState::pause()
{

}


void GameState::processEvents(sf::Event event)
{
    
	GameObject *player = nullptr;
	inputManager.update(event);

    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
		//Changed.
        pause_m = false;
		stateSwitch = true;
        nextStateS = "MenuState";
    }

	std::vector<GameObject *> players = gameData->getList(1);
	
	if (players.size() > 0)
	{
		player = players.at(0);

		if (!player->isTransitioningLevels())
		{
			//process controls
			//key a to move left
			if (inputManager.keyDown(sf::Keyboard::A))
			{
				player->moveLeft();
			}
			//key d to move right
			else if (inputManager.keyDown(sf::Keyboard::D))
			{
				player->moveRight();
			}
			//if neither control is down no movement
			else
			{
				player->stopHorizontalVelocity();
			}

			//key w to jump
			if (inputManager.keyPressed(sf::Keyboard::W))
			{
				if (player->getVerticalAcceleration() >= window->getSize().y)
					if (player->getVelocity().y == 0)
						player->jump();
			}

			if (inputManager.keyPressed(sf::Keyboard::Space))
			{
				player->fireProjectile();
			}
		}
	}

	if (players.size() > 1)//if two player
	{
		player = players.at(1);//player is player 2
		
		if (!player->isTransitioningLevels())
		{
			//process controls
			//key left to move left
			if (inputManager.keyDown(sf::Keyboard::Left))
			{
				player->moveLeft();
			}
			//key right to move right
			else if (inputManager.keyDown(sf::Keyboard::Right))
			{
				player->moveRight();
			}
			//if neither control is down no movement
			else
			{
				player->stopHorizontalVelocity();
			}

			//key up to jump
			if (inputManager.keyPressed(sf::Keyboard::Up))
			{
				if (player->getVerticalAcceleration() >= window->getSize().y)
					if (player->getVelocity().y == 0)
						player->jump();
			}

			if (inputManager.keyPressed(sf::Keyboard::Numpad0))
			{
				player->fireProjectile();
			}
		}
	}
 }


void GameState::process()
{
	//level .at(0)
	processIndividual(0);
	//pointtext .at(5)
	processIndividual(5);
	//pickup .at(3)
	processIndividual(3);
	//projectile .at(4)
	processIndividual(4);
	//monster .at(2)
	processIndividual(2);
	//player .at(1)
	processIndividual(1);

	//Delete the now dead objects.
	gameData->kill();
}


//Functional decomposition for general processing.
void GameState::processIndividual(unsigned int index)
{
	std::vector<GameObject *> data = gameData->getList(index);
	for (int i = 0; i < data.size(); i++)
	{
		data.at(i)->update();
	}
}


void GameState::draw()
{
	std::vector<std::vector<GameObject *>> data = gameData->getAll();

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			data.at(i).at(j)->render();
		}
	}
}