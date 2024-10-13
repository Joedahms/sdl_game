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
  const char* fontPath = "../16020_FUTURAM.ttf";

  const char* titleContent = "TRASHORE";
  SDL_Color titleColor = {255, 0, 255, 255};
  SDL_Rect titleRectangle = {100, 100, 0, 0,};
  this->title = std::make_unique<Text>(this->logFile, fontPath, titleContent, 24, titleColor, titleRectangle, renderer);

  SDL_Rect startButtonRectangle = {200, 150, 200, 50};
  this->startButton = std::make_unique<Button>(startButtonRectangle, "click", this->logFile, renderer);
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
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  this->startButton->render(renderer);
  this->title->render(renderer);
  SDL_RenderPresent(renderer);
}


