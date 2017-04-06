#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "GameObject.h"
#include "GameData.h"

class GameState : public BaseState
{
    public:
		GameState();
		GameState(sf::RenderWindow *);
		GameState(sf::RenderWindow *, bool);
        ~GameState();
        void pause();
        void processEvents(sf::Event);
        void process();
        void draw();
    private:
		void initialize(bool);
        sf::Vector2f playerPOS;
        void Cleanup();
		void processIndividual(unsigned int);
};

#endif // GAMESTATE_H