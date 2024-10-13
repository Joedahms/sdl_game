#include <string>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "main_menu.h"
#include "logger.h"

/*
 * Name: MainMenu
 * Purpose: Setup the game title and start button
 * Input:
 * - Path of the log file
 * - SDL renderer
 * Output: None
*/
MainMenu::MainMenu(std::string logFile, SDL_Renderer* renderer) {
  this->logFile = logFile;

  this->font = TTF_OpenFont("../16020_FUTURAM.ttf", 24);
  if (font == NULL) {
    writeToLogFile(this->logFile, TTF_GetError());
  }

  this->textColor = {255, 255, 255, 255};                                         // White
  SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, "SDL Game Engine", this->textColor);
  this->gameTitleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(gameTitleTexture, NULL, NULL, &this->gameTitleTextWidth, &this->gameTitleTextHeight);

  this->gameTitleRectangle = { 100, 100, this->gameTitleTextWidth, this->gameTitleTextHeight }; // Set position and size

  this->startButton = std::make_unique<Button>(200, 150, 200, 50, "click", this->font, this->logFile);
}

/*
 * Name: handleEvents
 * Purpose: Handle SDL events that occur in the main menu state
 * Input:
 * - Whether or not the game is running
 * Output: Current state the game is in
*/
int MainMenu::handleEvents(bool* gameIsRunning) {
  SDL_Event event;
  int returnValue = 0;
  while (SDL_PollEvent(&event) != 0) {  // While there are events in the queue
    switch(event.type) {                // Check which type of event
      case SDL_QUIT:                    // Quit
      *gameIsRunning = false; 
      break; 

      case SDL_MOUSEBUTTONDOWN:         // Mouse button was pressed
      if (this->startButton->checkHovered(event.motion.x, event.motion.y) == 0) { // If mouse is not over the button
        break;                          // Stay in main menu state
      }
      writeToLogFile(logFile, "Main menu button was pressed, switching to gameplay state");
      returnValue = 1;                  // Mouse was over button, switch to gameplay state
      break;

      default:
      break;
    }
  }
  return returnValue;
}

/*
 * Name: render
 * Purpose: Render the game title and the start button
 * Input:
 * - SDL renderer
 * Output: None
*/
void MainMenu::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, gameTitleTexture, NULL, &gameTitleRectangle);
  this->startButton->render(renderer);

  SDL_RenderPresent(renderer);
}


