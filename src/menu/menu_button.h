#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

class MenuButton {
	public:
		void init(SDL_Renderer*);
		void draw(SDL_Renderer*);
		void remove();
		void onPress();

	private:
		int xPosition;
		int yPosition;
		int width;
		int height;

		SDL_Texture* texture;
		SDL_Rect rect;

		basicColor color;
};

#endif
