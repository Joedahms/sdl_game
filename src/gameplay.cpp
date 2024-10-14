#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <assert.h>

#include "gameplay.h"
#include "logger.h"
#include "tile/tile_map.h"
#include "camera/camera.h"
#include "game_global.h"

/*
 * Name: Gameplay
 * Purpose: Set the global variables
 * Input:
 * - Global variables
 * Output: None
*/
Gameplay::Gameplay(struct GameGlobal gameGlobal) {
  this->gameGlobal = gameGlobal;
}

/*
 * Name: handleEvents
 * Purpose: Handle all events in the SDL event queue
 * Input:
 * - Whether or not the game is running
 * Output: The current state of the game after updating gameplay
*/
int Gameplay::handleEvents(bool* gameIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {            // While events in the queue
    switch(event.type) {
      case SDL_QUIT:                              // Quit event
      *gameIsRunning = false;
      break;
      
			case SDL_MOUSEWHEEL:                        // Mousewheel event
      if (event.wheel.y > 0) {                    // Scroll up -> zoom in
        if (this->tileMap->getTileSize() == 16) { // If not already zoomed in
          this->zoom_in_flag = true;
          this->zoom_out_flag = false;

          this->tileMap->setTileSize(32);
          this->camera->zoomIn(32);
          break;
        }
      }
      else if (event.wheel.y < 0) {               // Scroll down -> zoom out
        if (this->tileMap->getTileSize() == 32) { // If not already zoomed out
          this->zoom_in_flag = false;
          this->zoom_out_flag = true;

          this->tileMap->setTileSize(16);
          this->camera->zoomOut(16);
          break;
        }
      }

      default:
      break;
    }
  }
  return 1;                                       // Still in gameplay state
}

/*
 * Name: checkKeystates
 * Purpose: Perform the appropriate action depending on which keyboard key has been pressed
 * Input:
 * - None
 * Output: None
*/
void Gameplay::checkKeystates() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
	if (keystates[SDL_SCANCODE_UP]) {         // Up arrow
		this->camera->neg_y_dir();              // Move the camera up
		return;
	}
	else if (keystates[SDL_SCANCODE_DOWN]) {  // Down arrow
		this->camera->pos_y_dir();              // Move the camera down
		return;
	}
	else if (keystates[SDL_SCANCODE_RIGHT]) { // Right arrow
		this->camera->pos_x_dir();              // Move the camera right
		return;
	}
	else if (keystates[SDL_SCANCODE_LEFT]) {  // Left arrow
		this->camera->neg_x_dir();              // Move the camera left
		return;
	}
	else {                                    // No key pressed
		this->camera->zero_dir();               // Don't move the camera
	}
}

/* Name: setSelectedTile
 * Purpose: Determines where the mouse is and sets the tile it is over to selected
 * Input: None
 * Output: None
 */
void Gameplay::setSelectedTile() {
	int X; 
	int Y;
	Uint32 mouse = SDL_GetMouseState(&X, &Y);	

	int xCoordinate = floor(X / this->tileMap->getTileSize()) + this->camera->x_pos;      // X coordinate of moused over tile
	int yCoordinate = floor(Y / this->tileMap->getTileSize()) + this->camera->y_pos;      // X coordinate of moused over tile

  // Unselect all tiles
	for (int x = 0; x < this->camera->getVisibleXTiles() + this->camera->x_pos; x++) {
		for (int y = 0; y < this->camera->getVisibleYTiles() + this->camera->y_pos; y++) {
			this->tileMap->unselectTile(x, y);
		}
	}

	this->tileMap->selectTile(xCoordinate, yCoordinate);
}

/*
 * Name: Update
 * Purpose: Update the camera and set the selected tile
 * Input:
 * - None
 * Output: None
*/
void Gameplay::update() {
  writeToLogFile(this->gameGlobal.logFile, "updating in gameplay");
  this->camera->update(this->tileMap->getTotalXTiles(), this->tileMap->getTotalYTiles());	// update camera
  setSelectedTile();
}

/*
 * Name: render
 * Purpose: Render all gameplay elements
 * Input:
 * - None
 * Output: None
*/
void Gameplay::render() {
  // Print out camera position. Temporary for debugging
  std::cout << "cam x pos: " << this->camera->x_pos << std::endl;
	std::cout << "cam y pos: " << this->camera->y_pos << std::endl;

	SDL_RenderClear(this->gameGlobal.renderer);

	for (int x = 0; x < this->camera->getVisibleXTiles(); x++) {    // Loop through all visible x tiles
		for (int y = 0; y < this->camera->getVisibleYTiles(); y++) {  // Loop through all visible y tiles
			int currentXPosition = x + this->camera->x_pos;
			int currentYPosition = y + this->camera->y_pos;
			SDL_RenderCopy(this->gameGlobal.renderer, this->tileMap->getTileTexture(currentXPosition, currentYPosition), NULL, &(this->camera->destinationRect[x][y]));  // Render all visible tiles

			if (this->tileMap->getSelected(currentXPosition, currentYPosition)) {                       // If the current tile is selected
				SDL_RenderCopy(this->gameGlobal.renderer, this->selectedTexture, NULL, &(camera->destinationRect[x][y]));  // Render selected texture over it
			}
		}
	}
	SDL_RenderPresent(this->gameGlobal.renderer);
}

/*
 * Name: enterGameplay
 * Purpose: Perform necessary actions when the gameplay state is entered for the first time
 * Input:
 * - None
 * Output: None
*/
void Gameplay::enterGameplay() {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);

  // Initialize the camera
  writeToLogFile(this->gameGlobal.logFile, "Initializing camera");
  this->camera = std::make_unique<Camera>(windowSurface->h, windowSurface->w, 16);
  assert(this->camera->getScreenHeight() == windowSurface->h);
  assert(this->camera->getScreenWidth() == windowSurface->w);
  this->camera->zoomChange(16);
  writeToLogFile(this->gameGlobal.logFile, "Camera initialized");

  // Initialize the tile map
  writeToLogFile(this->gameGlobal.logFile, "Initializing tile map...");
  this->tileMap = std::make_unique<TileMap>(16, 200, 200, this->gameGlobal.renderer);
  writeToLogFile(this->gameGlobal.logFile, "Tile map initialized");

  initializeTextures();

  // State has been entered once
  this->stateEntered = true;
}

/*
 * Name: initializeTextures
 * Purpose: Initialize all textures in the gameplay state
 * Input:
 * - None
 * Output: None
*/
void Gameplay::initializeTextures() {
  writeToLogFile(this->gameGlobal.logFile, "Initializing textures...");
	SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
	selectedTexture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
  writeToLogFile(this->gameGlobal.logFile, "Textures initialized");
}

/*
 * Name: getStateEntered
 * Purpose: Check if the gameplay state has been entered before
 * Input: 
 * - None
 * Output: Whether the state has been entered before
*/
bool Gameplay::getStateEntered() {
  return this->stateEntered;
}
