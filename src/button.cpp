#include <iostream>

#include "button.h"
#include "logger.h"

Button::Button(int x, int y, int w, int h, const std::string& text, TTF_Font* font, std::string logFile) {
  rect = {x, y, w, h};
  color = {255, 0, 0, 255}; // Red
  this->text = text;
  this->font = font;
  this->logFile = logFile;
}

bool Button::checkHovered(int mouseXPosition, int mouseYPosition) {
  if (mouseXPosition < rect.x) {            // Outside left edge of button
    return false;
  }
  if (mouseXPosition > rect.x + rect.w) {   // Outside right edge of button
    return false;
  }
  if (mouseYPosition < rect.y) {            // Outside top edge of button
    return false;
  }
  if (mouseYPosition > rect.y + rect.h) {   // Outside bottom edge of button
    return false;
  }
  return true;
}

void Button::render(SDL_Renderer* renderer) {
    // Change color if hovered
    int mouseXPosition, mouseYPosition;
    SDL_GetMouseState(&mouseXPosition, &mouseYPosition);
    bool hovered = checkHovered(mouseXPosition, mouseYPosition);
    SDL_Color renderColor = hovered ? SDL_Color{0, 255, 0, 255} : color; // Green if hovered

    // Set draw color and fill the button
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Render button text
    SDL_Color textColor = {255, 255, 255, 255}; // White
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {rect.x + (rect.w - textW) / 2, rect.y + (rect.h - textH) / 2, textW, textH};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

