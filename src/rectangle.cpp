#include "SDL2/SDL.h"

#include "rectangle.h"

SDL_Rect centerRectangleHorizontal(const SDL_Surface* surface, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.x = surface->w / 2 - rectangle.w / 2;
  return centeredRectangle;
}

SDL_Rect centerRectangleVertical(const SDL_Surface* surface, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.y = surface->h / 2 - rectangle.h / 2;
  return centeredRectangle;
}
