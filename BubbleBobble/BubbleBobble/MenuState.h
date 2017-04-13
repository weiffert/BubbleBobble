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
	void processEvents(sf::Event);
};

#endif // MENUSTATE_H
