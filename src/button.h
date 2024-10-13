#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
  public:
  Button(int, int, int, int, const std::string&, TTF_Font*, std::string);

  bool checkHovered(int mouseXPosition, int mouseYPosition);
  void render(SDL_Renderer*);

  private:
  std::string text;             // Text to print inside the button
  std::string logFile;          // Path to the log file

  SDL_Rect backgroundRectangle; // Rectangle defining where to render the button to
  SDL_Color backgroundColor;    // Current color
  SDL_Color defaultColor;       // Color when not hovered
  SDL_Color hoveredColor;       // Color when hovered
  TTF_Font* textFont;           // Font of the text within the button
};

#endif
