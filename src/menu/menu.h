#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

class Menu {
	public:
		virtual void init(SDL_Renderer*) = 0;
		virtual void draw(SDL_Renderer*) = 0;
		virtual void remove() = 0;
};

#endif
