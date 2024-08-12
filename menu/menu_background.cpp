#include "menu_background.h"

MenuBackground::MenuBackground(SDL_Renderer* renderer, int xPos, int yPos, int width, int height) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;

	SDL_Surface* bgSurface = SDL_CreateRGBSurface(0, 3, 3, 32, 0, 0, 0, 0);	
	texture = SDL_CreateTextureFromSurface(renderer, bgSurface);
	SDL_FreeSurface(bgSurface);
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;
}

void MenuBackground::init(SDL_Renderer* renderer) {
	int i;
	/*
	SDL_Surface* bgSurface = SDL_CreateRGBSurface(0, 3, 3, 32, 0, 0, 0, 0);	
	texture = SDL_CreateTextureFromSurface(renderer, bgSurface);
	SDL_FreeSurface(bgSurface);
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;
	*/
}

void MenuBackground::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);	
}

void MenuBackground::remove() {
	int i;
}
