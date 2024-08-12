#include "main_menu.h"

void MainMenu::init(SDL_Renderer* renderer) {
	SDL_Surface* bgSurface = SDL_CreateRGBSurface(0, 3, 3, 32, 0, 0, 0, 0);	
	bgTex = SDL_CreateTextureFromSurface(renderer, bgSurface);
	SDL_FreeSurface(bgSurface);
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 100;
	bgRect.h = 100;
}

void MainMenu::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bgTex, NULL, &bgRect);	
}

void MainMenu::remove() {
	int i;
}
