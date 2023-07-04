#include "MainMenuComponent.h"






MainMenu::MainMenu(const char * texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}



MainMenu::~MainMenu()
{
}


void MainMenu::Update()
{

	srcRect.h = 640;
	srcRect.w = 800;

	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;

	destRect.w = srcRect.w * 1;
	destRect.h = srcRect.h * 1;

}

void MainMenu::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

