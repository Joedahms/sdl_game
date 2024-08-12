#include "main_menu.h"
#include "menu_background.h"

MainMenu::MainMenu(SDL_Renderer* renderer) {
	testBackground = std::make_unique<MenuBackground>(renderer, 0, 0, 100, 100);
}

// May not need this
void MainMenu::init(SDL_Renderer* renderer) {
}


void MainMenu::draw(SDL_Renderer* renderer) {
	testBackground->draw(renderer);
	/*
	SDL_RenderCopy(renderer, bgTex, NULL, &bgRect);	
	*/
}

void MainMenu::remove() {
	/*
	int i;
	*/
}
