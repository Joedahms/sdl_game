#include <iostream>
#include <memory>

#include "button.h"
#include "logger.h"

/*
 * Name: Button
 * Purpose: Set the properties of the button
 * Input:
 * - X position of the button
 * - Y position of the button
 * - Width of the button in pixels
 * - Height of the button in pixels
 * - The text to print in the middle of the button
 * - The font of the text
 * - Path to the log file
 * Output: None
*/
Button::Button(SDL_Rect rectangle, const std::string& text, std::string logFile, SDL_Renderer* renderer) {
  this->backgroundRectangle = rectangle;
  this->backgroundColor = {255, 0, 0, 255}; // Red
  this->hoveredColor = {0, 255, 0, 255};    // Green
  this->defaultColor = {255, 0, 0, 255};    // Red
  //this->text = text;
//  this->textFont = textFont;
  this->logFile = logFile;

  SDL_Color textColor = {255, 255, 0, 255};
  this->text = std::make_unique<Text>(this->logFile, "../16020_FUTURAM.ttf", "Start", 24, textColor, rectangle, renderer);
}

/*
 * Name: checkHovered
 * Purpose: Check if the mouse is over the button
 * Input:
 * - X position of the mouse
 * - Y position of the mouse
 * Output: Whether or not the mouse is over the button
*/
bool Button::checkHovered(int mouseXPosition, int mouseYPosition) {
  if (mouseXPosition < this->backgroundRectangle.x) {                               // Outside left edge of button
    return false;
  }
  if (mouseXPosition > this->backgroundRectangle.x + this->backgroundRectangle.w) { // Outside right edge of button
    return false;
  }
  if (mouseYPosition < this->backgroundRectangle.y) {                               // Outside top edge of button
    return false;
  }
  if (mouseYPosition > this->backgroundRectangle.y + this->backgroundRectangle.h) { // Outside bottom edge of button
    return false;
  }
  return true;
}

/*
 * Name: render
 * Purpose: Render the button
 * Input:
 * - The renderer to render the button with
 * Output: None
*/
void Button::render(SDL_Renderer* renderer) {
  // Change color if hovered
  int mouseXPosition, mouseYPosition;
  SDL_GetMouseState(&mouseXPosition, &mouseYPosition);  // Get the position of the mouse
  if (checkHovered(mouseXPosition, mouseYPosition)) {   // Mouse is hovered over the button
    this->backgroundColor = this->hoveredColor;         // Change to hovered color
  }
  else {                                                // Mouse is not hovered over the button
    this->backgroundColor = this->defaultColor;         // Change to default color
  }

  // Set draw color and fill the button
  SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(renderer, &this->backgroundRectangle);

  this->text->render(renderer);
  /*
  // Render button text
  SDL_Color textColor = {255, 255, 255, 255}; // White
  SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, text.c_str(), textColor);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

  int textW, textH;
  SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
  SDL_Rect textRect = {this->backgroundRectangle.x + (this->backgroundRectangle.w - textW) / 2, this->backgroundRectangle.y + (this->backgroundRectangle.h - textH) / 2, textW, textH};

  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


  SDL_FreeSurface(textSurface);
  */
  //SDL_DestroyTexture(textTexture);
}

