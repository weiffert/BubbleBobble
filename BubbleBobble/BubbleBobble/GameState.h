#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "GameObject.h"
#include "GameData.h"

class GameState : public BaseState
{
    public:
		GameState();
        GameState(bool);
        ~GameState();
        void pause();
        void processEvents(sf::RenderWindow &, sf::Event);
        void process(sf::RenderWindow &);
        void draw(sf::RenderWindow &);
    private:
        sf::Vector2f playerPOS;
        //std::vector<GameObject *> killList; No longer necessary. See GameData class. just run the kill function in the game state.
        void Cleanup();
        void PlayerMovement(GameObject&);
        void PlayerEvents(GameObject&, sf::Event &);
		void processIndividual(unsigned int);
        //sf::View camera;
};

#endif // GAMESTATE_H
