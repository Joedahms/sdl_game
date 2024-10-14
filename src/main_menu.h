#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "button.h"
#include "text.h"
#include "game_global.h"

class MainMenu {
  public:
  MainMenu(struct GameGlobal);
  int handleEvents(bool*);              // Handle SDL events while in the main menu state
  void render();                        // Render the main menu

  private:
  struct GameGlobal gameGlobal;
  std::string logFile;                  // Path to the log file
  std::unique_ptr<Text> title;          // Title of the game
  std::unique_ptr<Button> startButton;  // Button to launch the game
};

#endif
