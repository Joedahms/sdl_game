#include "main_menu.h"
#include "menu_background.h"
#include "menu_button.h"

MainMenu::MainMenu(SDL_Renderer* renderer) {
  std::unique_ptr<MenuBackground> testBackground = std::make_unique<MenuBackground>(renderer, 0, 0, 100, 100, RED);
  std::unique_ptr<MenuButton> testButton = std::make_unique<MenuButton>();
}

// May not need this
void MainMenu::init(SDL_Renderer* renderer) {
}


void MainMenu::draw(SDL_Renderer* renderer) {
	testBackground->draw(renderer);
}

void MainMenu::remove() {
	int i;
}
