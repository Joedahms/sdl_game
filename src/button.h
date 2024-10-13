#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
  public:
  Button(int, int, int, int, const std::string&, TTF_Font*, std::string);

  std::string text; 
  std::string logFile;

  SDL_Rect rect; 
  SDL_Color color; 
  TTF_Font* font;

  bool checkHovered(int mouseXPosition, int mouseYPosition);

  void render(SDL_Renderer*);
};

#endif
