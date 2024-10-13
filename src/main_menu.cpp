#include <string>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "main_menu.h"
#include "logger.h"

MainMenu::MainMenu(std::string logFile, SDL_Renderer* renderer) {
  this->logFile = logFile;

  this->font = TTF_OpenFont("../16020_FUTURAM.ttf", 24);
  if (font == NULL) {
    std::cout << TTF_GetError() << std::endl;
  }

  this->textColor = {255, 255, 255, 255}; // White color
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", textColor);
  this->textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(textTexture, NULL, NULL, &this->textWidth, &this->textHeight);

  this->renderQuad = { 100, 100, this->textWidth, this->textHeight }; // Set position and size

  testButton = std::make_unique<Button>(200, 150, 200, 50, "click", font, logFile);
}

int MainMenu::handleEvents(bool* gameIsRunning) {
  SDL_Event event;
  int returnValue = 0;
  while (SDL_PollEvent(&event) != 0) {  // While there are events
    switch(event.type) {                // Check which type of event
      case SDL_QUIT:                    // Quit
      *gameIsRunning = false; 
      break; 

      case SDL_MOUSEBUTTONDOWN:         // Mouse button was pressed
      if (this->testButton->checkHovered(event.motion.x, event.motion.y) == 0) { // If mouse is not over the button
        break;                                       // Stay in main menu state
      }
      writeToLogFile(logFile, "Main menu button was pressed, switching to gameplay state");
      returnValue = 1;                                         // Mouse was over button, switch to gameplay state
      break;

      default:
      break;
    }
  }
  return returnValue;
}

void MainMenu::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
  this->testButton->render(renderer);

  SDL_RenderPresent(renderer);
}
