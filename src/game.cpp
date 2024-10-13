#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <assert.h>

#include "game.h"
#include "camera/camera.h"
#include "logger.h"
#include "menu.h"

Game::Game(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen, std::string logFile) {
  writeToLogFile(logFile, "Constructing game...");
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  this->logFile = logFile;
  this->window = setupWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, fullscreen);

  // Initialize SDL
  writeToLogFile(logFile, "Initializing SDL...");
  try {
    int sdlInitReturn = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdlInitReturn != 0) {
      throw;
    }
  }
  catch (...) {
    writeToLogFile(logFile, "Failed to initialize SDL");
    exit(1);
  }
  writeToLogFile(logFile, "SDL initialized");

  // Create renderer
  writeToLogFile(logFile, "Creating renderer");
  try {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
      throw;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  }
  catch (...) {
    writeToLogFile(logFile, "Error creating renderer");
    exit(1);
  }
  writeToLogFile(logFile, "Renderer created");

  // Initialize TTF
  writeToLogFile(logFile, "Initializing TTF...");
  try {
    int ttfInitReturn = TTF_Init();
    if (ttfInitReturn == -1) {
      throw;
    }
  }
  catch (...) {
    writeToLogFile(logFile, "Failed to initialize TTF");
    exit(1);
  }
  writeToLogFile(logFile, "TTF initialized");
  
  

  // Create and initialize main menu
  this->mainMenu = std::make_unique<MainMenu>(this->logFile, this->renderer);
  
  this->gameplay = std::make_unique<Gameplay>(this->logFile);

  // use factory to create objects here
  //std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
  //player_vec.emplace_back(std::move(player));
  //player_vec[0]->print();
  //player->print();
  
  prev_ticks = SDL_GetTicks();	// first physics tick count
  gameIsRunning = true;
}

SDL_Window* Game::setupWindow(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen) {
  writeToLogFile(logFile, "Creating SDL game window...");
  int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

  // Create the window
  try {
    window = SDL_CreateWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, flags);
    return window;
  }
  catch(...) {
    writeToLogFile(logFile, "Error setting up SDL game window");
    exit(1);
  }
  writeToLogFile(logFile, "SDL game window created");
}

void Game::checkState() {
  switch(this->state) {
    case 0:
    if (!this->mainMenuStateInitialized) {
    
    }
    break;

    case 1:
    if (!this->gameplay->getStateEntered()) {
      this->gameplay->enterGameplay(this->screenHeight, this->screenWidth, this->renderer);  
    }
    break;

    case 2:
    if (!this->pauseMenuStateInitialized) {
      
    }
    break;

    default:
    break;
  }
}

/*
 * Name: handleEvents
 * Purpose: Check if SDL event has occured and handle accordingly
 * Input: None
 * Output: None
 */
void Game::handleEvents() {
	//SDL_Event event;
	//while (SDL_PollEvent(&event) != 0) {    // SDL event occured
    switch (this->state) {
      case 0: // Main menu
      this->state = this->mainMenu->handleEvents(&this->gameIsRunning);
      break;
      case 1: // Gameplay
      this->state = this->gameplay->handleEvents(&this->gameIsRunning);
      break;
      case 2: // Pause menu
      // this->pauseMenu->handleEvents();
      break;
      default:
      break;
    }



    /*
		switch (event.type) {                 // Which type of event occured
			case SDL_QUIT:                      // Quit event
        gameIsRunning = false;
        return;
			case SDL_MOUSEWHEEL:                // Mousewheel event
				if (event.wheel.y > 0) {          // Scroll up -> zoom in
					if (tileMap->getTileSize() == 16) {
						zoom_in_flag = true;
						zoom_out_flag = false;

						tileMap->setTileSize(32);
						camera->zoomIn(32);	
					}
				}
				else if (event.wheel.y < 0) {     // Scroll down -> zoom out
          if (tileMap->getTileSize() == 32) {
						zoom_in_flag = false;
						zoom_out_flag = true;

						tileMap->setTileSize(16);
						camera->zoomOut(16);
					}
				}
        break;                        

      case SDL_MOUSEMOTION:
        this->mainMenu->testButton->checkHovered(event);
        break;

      case SDL_MOUSEBUTTONDOWN:
        this->mainMenu->testButton->checkPressed(event);
        break;

      default:
        break;
		}
    */
	//}
}

void Game::checkKeystates()
{
  switch(this->state) {
    case 0:
    break;

    case 1:
    this->gameplay->checkKeystates();
    break;

    case 2:
    break;

    default:
    break;
  }

}

/* Name: setSelectedTile
 * Purpose: Determines where the mouse is and sets the tile it is over to selected
 * Input: None
 * Output: None
 */
/*
void Game::setSelectedTile() {
	int X; 
	int Y;
	Uint32 mouse = SDL_GetMouseState(&X, &Y);	

	int xCoordinate = floor(X / tileMap->getTileSize()) + camera->x_pos;			// x coordinate of moused over tile
	int yCoordinate = floor(Y / tileMap->getTileSize()) + camera->y_pos;			// y coordinate of moused over tile

	for (int x = 0; x < camera->getVisibleXTiles() + camera->x_pos; x++)
	{
		for (int y = 0; y < camera->getVisibleYTiles() + camera->y_pos; y++)
		{
			tileMap->unselectTile(x, y);
		}
	}
	tileMap->selectTile(xCoordinate, yCoordinate);
}
*/

/*
 * Name: update
 * Purpose: Execute actions every game loop
 * Input: None
 * Output: None
 */
void Game::update() {
	current_ticks = SDL_GetTicks();	

	delta_time = current_ticks - prev_ticks;		// calc delta time from ticks
	total_delta_time += delta_time;				// num used to check if time to update
	prev_ticks = current_ticks;				// set prev ticks

	if (total_delta_time >= 128)				// update if it is time
	{
		total_delta_time = 0;				// reset counter
    switch(this->state) {
      case 0:
      break;
      case 1:
      this->gameplay->update();
      break;
      case 2:
      break;
      default:
      break;
    } 
		//camera->update(tileMap->getTotalXTiles(), tileMap->getTotalYTiles());	// update camera
		//setSelectedTile();
	}
}

void enterMainMenuState() {

}

void enterGameplayState() {

}

void enterPauseMenuState() {

}

/*
 * Name: render
 * Purpose: Either renders textures directly or calls functions to render
 * Input: None
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
void Game::renderGameplay() {
  // Print out camera position. Temporary for debugging
  std::cout << "cam x pos: " << camera->x_pos << std::endl;
	std::cout << "cam y pos: " << camera->y_pos << std::endl;

	SDL_RenderClear(renderer);

	for (int x = 0; x < camera->getVisibleXTiles(); x++)		// visible x tiles
	{
		for (int y = 0; y < camera->getVisibleYTiles(); y++)	// visible y tiles
		{
			int currentXPosition = x + camera->x_pos;
			int currentYPosition = y + camera->y_pos;
			SDL_RenderCopy(renderer, tileMap->getTileTexture(currentXPosition, currentYPosition), NULL, &(camera->destinationRect[x][y]));	// render all visible tiles

			if (tileMap->getSelected(currentXPosition, currentYPosition))							// if selected
			{
				SDL_RenderCopy(renderer, selectedTexture, NULL, &(camera->destinationRect[x][y]));		// render selected texture over it
			}
		}
	}
  testButton->render(renderer);
	SDL_RenderPresent(renderer);
}
*/

/*
 * Name: clean
 * Purpose: Frees SDL resources and quits
 * Input: None
 * Output: None
 */
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
