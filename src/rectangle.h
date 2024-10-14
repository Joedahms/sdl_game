#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>

template <typename T>
SDL_Rect centerRectangleHorizontal(T centerWithin, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.x = (centerWithin->w / 2 - rectangle.w / 2);
  return centeredRectangle;
}

template <typename T>
SDL_Rect centerRectangleVertical(T centerWithin, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.y = (centerWithin->h / 2 - rectangle.h / 2);
  return centeredRectangle;
}

template <>
inline SDL_Rect centerRectangleHorizontal<SDL_Rect*>(SDL_Rect* centerWithin, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.x = (centerWithin->w / 2 - rectangle.w / 2) + centerWithin->x;
  return centeredRectangle;
}

template <>
inline SDL_Rect centerRectangleVertical<SDL_Rect*>(SDL_Rect* centerWithin, const SDL_Rect rectangle) {
  SDL_Rect centeredRectangle = rectangle;
  centeredRectangle.y = (centerWithin->h / 2 - rectangle.h / 2) + centerWithin->y;
  return centeredRectangle;
}

#endif
