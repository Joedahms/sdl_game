#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <assert.h>

#include "game.h"
#include "camera/camera.h"
#include "logger.h"
#include "menu.h"

/*
 * Name: Game
 * Purpose: Construct the game object and set up relevant components
 * Input:
 * - The title of the game window
 * - X position of the game window
 * - Y position of the game window
 * - The width of the game window
 * - The height of the game window
 * - Whether or not the game window should be fullscreen
 * - The path of the logfile relative to the main function
 * Output: None
*/
Game::Game(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen, std::string logFile) {
  writeToLogFile(logFile, "Constructing game...");
  this->screenWidth = screenWidth;              // Set the width of the game window
  this->screenHeight = screenHeight;            // Set the height of the game window
  this->logFile = logFile;                      // Set the path of the log file
  this->window = setupWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, fullscreen); // Setup the SDL game window

  initializeSdl(this->window);                  // Initialize SDL and its components

  // Initialize states
  this->mainMenu = std::make_unique<MainMenu>(this->logFile, this->renderer); // Main menu
  this->gameplay = std::make_unique<Gameplay>(this->logFile);                 // Gameplay
  
  this->previousTicks = SDL_GetTicks();         // First physics tick count
  gameIsRunning = true;                         // Game is now running
  writeToLogFile(logFile, "Game constructed");
}

/*
 * Name: setupWindow
 * Purpose: Setup the SDL game window
 * Input:
 * - The name of the window
 * - The X position of the window on the user's screen
 * - The Y position of the window on the user's screen
 * - The width of the screen in pixels
 * - The height of the screen in pixels
 * - Whether or not the game window should be fullscreen
 * Output:
 * - Pointer to the game window
*/
SDL_Window* Game::setupWindow(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen) {
  writeToLogFile(logFile, "Creating SDL game window...");

  // Check for fullscreen
  int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

  // Create the SDL window
  try {
    return SDL_CreateWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, flags);
  }
  catch(...) {
    writeToLogFile(logFile, "Error setting up SDL game window");
    exit(1);
  }
  writeToLogFile(logFile, "SDL game window created");
}

/*
 * Name: initializeSdl
 * Purpose: Setup SDL, the renderer, and TTF
 * Input:
 * - The game window
 * Output: None
*/
void Game::initializeSdl(SDL_Window* window) {
  // Initialize SDL
  writeToLogFile(this->logFile, "Initializing SDL...");
  try {
    int sdlInitReturn = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdlInitReturn != 0) {
      throw;
    }
  }
  catch (...) {
    writeToLogFile(this->logFile, "Failed to initialize SDL");
    exit(1);
  }
  writeToLogFile(this->logFile, "SDL initialized");

  // Create renderer
  writeToLogFile(this->logFile, "Creating renderer");
  try {
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
      throw;
    }
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
  }
  catch (...) {
    writeToLogFile(this->logFile, "Error creating renderer");
    exit(1);
  }
  writeToLogFile(this->logFile, "Renderer created");

  // Initialize TTF
  writeToLogFile(this->logFile, "Initializing TTF...");
  try {
    int ttfInitReturn = TTF_Init();
    if (ttfInitReturn == -1) {
      throw;
    }
  }
  catch (...) {
    writeToLogFile(this->logFile, "Failed to initialize TTF");
    exit(1);
  }
  writeToLogFile(this->logFile, "TTF initialized");
}

/*
 * Name: checkState
 * Purpose: Check which state the game is in. If there was a state switch and the current state
 * has not been entered before, run its enter method.
 * Input:
 * - None
 * Output: None
*/
void Game::checkState() {
  switch(this->state) {
    case 0: // Main menu
    break;

    case 1: // Gameplay
    if (!this->gameplay->getStateEntered()) {
      this->gameplay->enterGameplay(this->screenHeight, this->screenWidth, this->renderer);  
    }
    break;

    case 2: // Pause menu
    break;

    default:
    break;
  }
}

/*
 * Name: handleEvents
 * Purpose: Check the current state, and call that state's handle events method
 * Input:
 * - None
 * Output: None
 */
void Game::handleEvents() {
  switch (this->state) {
    case 0: // Main menu
    this->state = this->mainMenu->handleEvents(&this->gameIsRunning);
    break;

    case 1: // Gameplay
    this->state = this->gameplay->handleEvents(&this->gameIsRunning);
    break;

    case 2: // Pause menu
    break;

    default:
    break;
  }
}

/*
 * Name: checkKeystates
 * Purpose: Check the current state of the game and call that state's method to check the key states
 * Input:
 * - None
 * Output: None
*/
void Game::checkKeystates()
{
  switch(this->state) {
    case 0: // Main menu
    break;

    case 1: // Gameplay
    this->gameplay->checkKeystates();
    break;

    case 2: // Pause menu
    break;

    default:
    break;
  }
}

/*
 * Name: update
 * Purpose: First check if it's time to update. If it is, reset the time since last update. Then check the current
 * state and call that state's function to update
 * Input:
 * - None
 * Output: None
 */
void Game::update() {
  
  // Calculate values used to check if it's time to update
	this->currentTicks = SDL_GetTicks();                          // Ticks at this very moment
	this->deltaTime = this->currentTicks - this->previousTicks;   // Time since this funnction was last executed
	this->totalDeltaTime += this->deltaTime;                      // Add the time since the function was last executed to the time the game was last updated
	this->previousTicks = this->currentTicks;

	if (this->totalDeltaTime >= 128) {                            // Check if it is time to update
		this->totalDeltaTime = 0;                                   // Reset time since last update
    switch(this->state) {                                       // Check current state
      case 0:                                                   // Main menu
      break;

      case 1:                                                   // Gameplay
      this->gameplay->update();
      break;

      case 2:                                                   // Pause menu
      break;

      default:
      break;
    } 
	}
}

/*
 * Name: renderState
 * Purpose: Check current state and call that state's function to render
 * Input: 
 * - None
 * Output: None
 */
void Game::renderState() {
  switch(this->state) {
    case 0: // Main menu
    this->mainMenu->render(renderer);
    break;

    case 1: // Gameplay
    this->gameplay->render(renderer);
    break;

    case 2: // Pause menu
    break;

    default:
    break;
  }
}

/*
 * Name: clean
 * Purpose: Frees SDL resources and quits
 * Input: 
 * - None
 * Output: None
 */
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
  writeToLogFile(logFile, "Game cleaned");
}
