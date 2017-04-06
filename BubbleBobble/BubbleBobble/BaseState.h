#ifndef BASESTATE_H
#define BASESTATE_H

#include <string>
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "InputManager.h"


class BaseState
{
	public:
		BaseState();
        BaseState(sf::RenderWindow *);
        ~BaseState();
        //Allows states to stop and switch between each other.
        //Planned to be use to stop GameState and switch to MenuState.
        bool pause();
        //Processes keyboard events, handles Entities, DynamicEnvironment,
        //StaticEnvironment, and collisionDetection for every state
        virtual void processEvents(sf::Event);
        //Processes game logic not dependent on events
        virtual void process();
        //Draws all objects to the window
        virtual void draw();
        //Deletes everything that the fileManager has loaded
        bool switchTrue();
        std::string nextState();
		void unload();
		GameData * getGameDataPTR();

    protected:
        bool stateSwitch;
        std::string nextStateS;
		bool pause_m;
        //Contains the address of a text file that includes all the files needed for the state.
        //This string is passed to the FileManager which goes to the text file and grabs all the files
        //that the text file asks for.
        //If the GameState calls on the FileManager it also needs to include a number for the level it needs to load.
        std::string folder;
        //Handles all the input that is detected in the Game class and returns which keys were pressed to the state
		InputManager inputManager;
		GameData *gameData;
		sf::RenderWindow *window;
};
#endif // BASESTATE_H
