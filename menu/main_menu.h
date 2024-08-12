#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SDL2/SDL.h>
#include <memory>

#include "menu.h"
#include "menu_element.h"

class MainMenu : public Menu {
	public:
		MainMenu(SDL_Renderer*);
		void init(SDL_Renderer*);
		void draw(SDL_Renderer*);
		void remove();
				
	private:
		std::unique_ptr<MenuElement> testBackground;
		// Buttons
		// Backgrounds	

		//SDL_Texture* bgTex;
		//SDL_Rect bgRect;

};

#endif
