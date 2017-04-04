#ifndef MENUSTATE_H
#define MENUSTATE_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BaseState.h"

class MenuState : public BaseState
{
    public:
        MenuState();
		MenuState(sf::RenderWindow*);
        ~MenuState();
        void pause();
        void processEvents(sf::Event);
        void process();
        void draw();

    private:
        sf::View centered;
};

#endif // MENUSTATE_H
