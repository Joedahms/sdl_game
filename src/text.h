#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game_global.h"

class Text {
  public:
  Text(struct GameGlobal, const char*, const char*, int, SDL_Color, SDL_Rect);
  SDL_Rect centerHorizontal();
  SDL_Rect centerVertical();
  void render();

  private:
  struct GameGlobal gameGlobal;
  TTF_Font* font;
  const char* content;
  int fontSize;
  SDL_Color color;
  SDL_Texture* texture;
  SDL_Rect rectangle;
};

#endif
