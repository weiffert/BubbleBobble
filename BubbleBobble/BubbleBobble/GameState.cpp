#include "stdafx.h"
#include "GameState.h"
#include "Level.h"
#include "Player.h"

GameState::GameState()
{
	//create the level.
	gameData = new GameData();
	GameObject *level = new Level("Level0");

	//create the players.
	gameData->add(0, level);
	GameObject *player1 = new Player("Player1");
	gameData->add(1, player1);
}

GameState::GameState(bool twoPlayer)
{
	//create the level.
	gameData = new GameData();
	GameObject *level = new Level("Level0");

	//create the players.
	gameData->add(0, level);
	GameObject *player1 = new Player("Player1");
	gameData->add(1, player1);
	if (twoPlayer)
	{
		GameObject *player2 = new Player("Player2");
		gameData->add(1, player2);
	}
}

GameState::~GameState()
{
    //dtor
}

void GameState::pause()
{

}

void GameState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
	
	/*
    //Loops through all entities
    for(int i = 0; i < objectVector.size(); i++)
    {	
		enum player {2};
		if (objectVector.at(player).at(i)->update() == false)
			killist.push_back(objectVector.at(player).at(i));
    }
	*/
 }

void GameState::process(sf::RenderWindow &window)
{
	/*//Loops through all entities
    for(int i = 0; i < objectVector.size(); ++i)
    {
        //Loops through entities ID's
        for(int r = 0; r < objectVector.at(i)->getID().size(); r++ )
        {
            //Handles Entities with playerMovement ID
            if( objectVector.at(i)->getID().at(r) == "playerMovement")
            {
                PlayerMovement(*objectVector.at(i));

            }
            if( objectVector.at(i)->getID().at(r) == "gravity")
            {
                gravity(*objectVector.at(i));
            }
            if(objectVector.at(i)->getID().at(r) == "moves")
            {
                collide(*objectVector.at(i));
            }
        }
    }
	*/

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

//Moves the player based on keyboard input
void GameState::PlayerMovement(GameObject& player)
{

}
void GameState::PlayerEvents(GameObject& player, sf::Event& event)
{
  
}
void GameState::draw(sf::RenderWindow & window)
{
	window.clear();

	std::vector<std::vector<GameObject *>> data = gameData->getAll();

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); i++)
		{
			data.at(i).at(j)->render();
		}
	}

	window.display();
}

void GameState::Cleanup()
{
	gameData->kill();
}
