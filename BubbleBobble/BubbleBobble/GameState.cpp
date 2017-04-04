#include "stdafx.h"
#include "GameState.h"
#include "Level.h"
#include "Player.h"


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
	initialize(false);
}


GameState::~GameState()
{
	delete gameData;
    //dtor
}


void GameState::initialize(bool twoPlayer)
{
	//create the level.
	gameData = new GameData();
	GameObject *level = new Level("Level0");
	level->initialize(window, gameData);

	//create the players.
	gameData->add(0, level);
	GameObject *player1 = new Player("Player1");
	gameData->add(1, player1);
	player1->initialize(window, gameData);
	if (twoPlayer)
	{
		GameObject *player2 = new Player("Player2");
		gameData->add(1, player2);
		player2->initialize(window, gameData);
	}
}


void GameState::pause()
{

}


void GameState::processEvents(sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
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

    Cleanup();
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
	window->clear();

	std::vector<std::vector<GameObject *>> data = gameData->getAll();

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); i++)
		{
			data.at(i).at(j)->render();
		}
	}

	window->display();
}

void GameState::Cleanup()
{
	gameData->kill();
}
