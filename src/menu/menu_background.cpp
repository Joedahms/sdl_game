#include <iostream>
#include "menu_background.h"

MenuBackground::MenuBackground(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, basicColor color) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;

	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;

	this->color = color;
	
}

// May not need this
void MenuBackground::init(SDL_Renderer* renderer) {
	int i;
}

void MenuBackground::draw(SDL_Renderer* renderer) {
	switch (color) {
		case RED:
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			break;
		case GREEN:
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
			break;
		case BLUE:
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
			break;
		case WHITE:
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			break;
		case BLACK:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			break;

		default:
			std::cout << "Invalid Color Selected" << std::endl;
	}

	//SDL_SetRenderDrawColor(renderer, 128, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
	// Removed due to switching to RenderFillRect
	//SDL_RenderCopy(renderer, texture, NULL, &rect);	
}

void MenuBackground::remove() {
	int i;
}
