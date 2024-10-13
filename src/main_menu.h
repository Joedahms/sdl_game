#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "button.h"

class MainMenu {
  public:
  MainMenu(std::string, SDL_Renderer*);
  int handleEvents(bool*);              // Handle SDL events while in the main menu state
  void render(SDL_Renderer*);           // Render the main menu

  private:
  std::string logFile;                  // Path to the log file

  TTF_Font* font;                       // Font for all elements in the main menu
  SDL_Color textColor;                  // Text color for all elements in the main menu
  SDL_Texture* gameTitleTexture;

  int gameTitleTextWidth;               // Width of the game title in pixels
  int gameTitleTextHeight;              // Height of the game title in pixels

  SDL_Rect gameTitleRectangle;

  std::unique_ptr<Button> startButton;  // Button to launch the game
};

#endif
