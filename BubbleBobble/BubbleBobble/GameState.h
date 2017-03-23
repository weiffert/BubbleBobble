#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "GameObject.h"
#include "GameData.h"

class GameState : public BaseState
{
    public:
        GameState(std::string  = "Level_1");
        ~GameState();
        void pause();
        void processEvents(sf::RenderWindow &, sf::Event);
        void process(sf::RenderWindow &);
        void draw(sf::RenderWindow &);
		GameData * getGameDataPTR();
    private:
        sf::Vector2f playerPOS;
        //std::vector<GameObject *> killList; No longer necessary. See GameData class. just run the kill function in the game state.
        void Cleanup();
        void collide(GameObject&);
        void PlayerMovement(GameObject&);
        void PlayerEvents(GameObject&, sf::Event &);
        void gravity(GameObject&);
        //sf::View camera;
		GameData *gameData;
};

#endif // GAMESTATE_H
