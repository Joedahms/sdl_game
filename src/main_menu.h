#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "button.h"

class MainMenu {
  public:
  MainMenu(std::string, SDL_Renderer*);
  int handleEvents(bool*);
  void render(SDL_Renderer*);

  private:
  std::string logFile;

  TTF_Font* font;
  SDL_Color textColor;
  SDL_Texture* textTexture;

  int textWidth;
  int textHeight;

  SDL_Rect renderQuad;

  std::unique_ptr<Button> testButton;
};

#endif
