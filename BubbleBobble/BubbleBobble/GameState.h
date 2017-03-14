#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseState.h>
#include "GameObject.h"

class GameState : public BaseState
{
    public:
        GameState(std::string  = "Level_1");
        ~GameState();
        void pause();
        void processEvents(sf::RenderWindow &, sf::Event);
        void process(sf::RenderWindow &);
        void draw(sf::RenderWindow &);
    private:
        sf::Vector2f playerPOS;
        std::vector<GameObject *> killList;
        void Cleanup();
        void collide(GameObject&);
        void PlayerMovement(GameObject&);
        void PlayerEvents(GameObject&, sf::Event &);
        void gravity(GameObject&);
        sf::View camera;
};

#endif // GAMESTATE_H
