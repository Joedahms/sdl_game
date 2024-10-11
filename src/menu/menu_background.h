#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include "menu_element.h"

class MenuBackground : public MenuElement {
	public:
		MenuBackground(SDL_Renderer*, int, int, int, int, basicColor);
		void init(SDL_Renderer*);
		void draw(SDL_Renderer*);
		void remove();

	private:
		int xPos;
		int yPos;
		int width;
		int height;

		SDL_Texture* texture;
		SDL_Rect rect;

		basicColor color;
		//
		// color
		// border
		// position
};

#endif
