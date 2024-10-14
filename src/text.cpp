#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "text.h"
#include "logger.h"
#include "rectangle.h"

Text::Text(struct GameGlobal gameGlobal, const char* fontPath, const char* content, int fontSize, SDL_Color color, SDL_Rect rectangle) {
  this->gameGlobal = gameGlobal;

  this->content = content;
  this->fontSize = fontSize;

  this->font = TTF_OpenFont(fontPath, this->fontSize);
  if (this->font == NULL) {
    writeToLogFile(this->gameGlobal.logFile, TTF_GetError());
  }

  this->color = color;
  this->rectangle = rectangle;

  SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, this->content, this->color);
  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(this->texture, NULL, NULL, &this->rectangle.w, &this->rectangle.h);
}

SDL_Rect Text::centerHorizontal() {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  SDL_Rect centeredRectangle = centerRectangleHorizontal(windowSurface, this->rectangle);
  return centeredRectangle;
}

SDL_Rect Text::centerVertical() {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  SDL_Rect centeredRectangle = centerRectangleVertical(windowSurface, this->rectangle);
  return centeredRectangle;
}

void Text::render() {
  SDL_RenderCopy(this->gameGlobal.renderer, this->texture, NULL, &this->rectangle);
}
