#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "text.h"
#include "logger.h"

Text::Text(std::string logFilePath, const char* fontPath, const char* content, int fontSize, SDL_Color color, SDL_Rect rectangle, SDL_Renderer* renderer) {
  this->logFile = logFilePath;
  this->content = content;
  this->fontSize = fontSize;

  this->font = TTF_OpenFont(fontPath, this->fontSize);
  if (this->font == NULL) {
    writeToLogFile(this->logFile, TTF_GetError());
  }

  this->color = color;
  this->rectangle = rectangle;

  SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, this->content, this->color);
  this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(this->texture, NULL, NULL, &this->rectangle.w, &this->rectangle.h);
}

void Text::render(SDL_Renderer* renderer) {
  //SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, this->texture, NULL, &this->rectangle);
}
