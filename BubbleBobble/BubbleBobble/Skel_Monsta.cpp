#include "stdafx.h"
#include "Skel_Monsta.h"


Skel_Monsta::Skel_Monsta()
{
	name = "Skel_Monsta";
	window = nullptr;
	gameData = nullptr;
}


Skel_Monsta::Skel_Monsta(sf::RenderWindow *win, GameData *data)
{
	name = "Skel_Monsta";
	window = win;
	gameData = data;
	setTexture("../textures/Characters/skelMonsta.png");
	flipTexture();
}


Skel_Monsta::~Skel_Monsta()
{
}
