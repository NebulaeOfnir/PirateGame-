#pragma once
#ifndef MainMenuComponent_h
#define MainMenuComponent_h


#include <string>
#include "Game.h"
#include "SDL.h"
#include "TextureMngr.h"

using namespace std;

class MainMenu
{
	int xpos;
	int ypos;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;

public:

	MainMenu(const char *texturesheet, int x, int y);
	~MainMenu();

	void Update();
	void Render();


};

#endif