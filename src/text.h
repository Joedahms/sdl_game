#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {
  public:
  Text(std::string, const char*, const char*, int, SDL_Color, SDL_Rect, SDL_Renderer*);
  void render(SDL_Renderer*);

  private:
  std::string logFile;

  TTF_Font* font;
  const char* content;
  int fontSize;
  SDL_Color color;
  SDL_Texture* texture;
  SDL_Rect rectangle;
};

#endif
