#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <SDL2/SDL.h>

enum basicColor { RED, GREEN, BLUE, WHITE, BLACK };

class MenuElement {
	public: 
		virtual void init(SDL_Renderer*) = 0;
		virtual void draw(SDL_Renderer*) = 0;
		virtual void remove() = 0;
};

#endif
