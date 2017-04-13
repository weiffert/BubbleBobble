#ifndef SPLASHSCREENSTATE_H
#define SPLASHSCREENSTATE_H

#include "BaseState.h"


class SplashScreenState : public BaseState
{
public:
	//Constructor initializes file directory, keyList, and loads
	SplashScreenState();
	SplashScreenState(sf::RenderWindow *);
	~SplashScreenState();
	//Checks if any key is pressed. If a key is pressed go to menu state
	void processEvents(sf::Event);
	//Draws the background for the splash screen
	void draw();

};

#endif // SPLASHSCREENSTATE_H
