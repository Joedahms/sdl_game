#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SDL2/SDL.h>

#include "menu.h"

class MainMenu : public Menu {
	public:
		void init(SDL_Renderer*);
		void draw(SDL_Renderer*);
		void remove();
				
	private:
		// buttons
		// backgrounds
		
		//
		SDL_Texture* bgTex;
		SDL_Rect bgRect;

};

#endif
