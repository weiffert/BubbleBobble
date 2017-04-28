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
	void draw();
private:
	unsigned int selection = 0;
	sf::RectangleShape menuScreen;
	sf::Texture menuTexture;
};

#endif // MENUSTATE_H