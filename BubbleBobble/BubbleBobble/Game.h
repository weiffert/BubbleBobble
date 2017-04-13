#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "SplashScreenState.h"


class Game
{
    public:
        Game();
        ~Game();
        //Runs the game loop which runs every game process
        //The game loop has a fixed time step based on FPS_m
        void loop();

    private:
        int FPS_m;
        sf::RenderWindow *window;
        sf::Vector2i screenDimensions;
        StateManager stateManager;
};

#endif // GAME_H
