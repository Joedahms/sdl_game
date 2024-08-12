#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include "menu_element.h"

class MenuBackground : public MenuElement {
	public:
		void init(SDL_Renderer*);
		void draw(SDL_Renderer*);
		void remove();

	private:
		// color
		// border
		// position
};

#endif
