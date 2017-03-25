#include "stdafx.h"
#include "GameState.h"
#include "Level.h"
#include "Player.h"

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
        //Loops through entities ID's
        for(int r = 0; r < objectVector.at(i)->getID().size(); r++ )
        {
            if( objectVector.at(i)->getID().at(r) == "playerEvents")
            {
                PlayerEvents(*objectVector.at(i), event);
            }
        }
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

	//level
	//pointtext
	//pickup
	//projectile
	//monster
	//player

    Cleanup();
}

void GameState::gravity(GameObject& entity)
{
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
	/*
	window.setView(camera);
	//Loops through all entities
	for(int i = 0; i < objectVector.size(); i++)
	{
	for (int r = 0; r < objectVector.at(i).size(); r++)
	{
	window.draw(objectVector.at(i).at(r)->getRectangle());
	}
	}
	*/

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
	/*
    for(int i = 0; i < killList.size(); i++)
    {
        for(int x = 0; x < objectVector.size(); x++)
        {
            if(objectVector.at(x) == killList.at(i))
				objectVector.erase(objectVector.begin() + x);
        }
    }
	*/
	gameData->kill();
}

GameData * GameState::getGameDataPTR()
{
	return gameData;
}