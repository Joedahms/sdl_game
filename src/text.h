#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game_global.h"
#include "rectangle.h"

class Text {
  public:
  Text(struct GameGlobal, const char*, const char*, int, SDL_Color, SDL_Rect);

  template <typename T>
  void centerHorizontal(T centerWithin) {
    this->rectangle = centerRectangleHorizontal(centerWithin, this->rectangle);  
  }

  template <typename T>
  void centerVertical(T centerWithin) {
    this->rectangle = centerRectangleVertical(centerWithin, this->rectangle);
  }

  //SDL_Rect centerVertical();
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
