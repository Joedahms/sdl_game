#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <assert.h>

#include "gameplay.h"
#include "logger.h"
#include "tile_map.h"
#include "camera/camera.h"

Gameplay::Gameplay(std::string logFile) {
  this->logFile = logFile;
}

int Gameplay::handleEvents(bool* gameIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch(event.type) {
      case SDL_QUIT:                      // Quit event
      *gameIsRunning = false;
      break;
      
			case SDL_MOUSEWHEEL:                // Mousewheel event
      if (event.wheel.y > 0) {            // Scroll up -> zoom in
        if (this->tileMap->getTileSize() == 16) {
          this->zoom_in_flag = true;
          this->zoom_out_flag = false;

          this->tileMap->setTileSize(32);
          this->camera->zoomIn(32);	
          break;
        }
      }
      else if (event.wheel.y < 0) {       // Scroll down -> zoom out
        if (this->tileMap->getTileSize() == 32) {
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
  return 1;
}

void Gameplay::checkKeystates() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
	if (keystates[SDL_SCANCODE_UP]) {       // Up arrow
		this->camera->neg_y_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_DOWN])	// down arrow
	{
		this->camera->pos_y_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_RIGHT])	// right arrow
	{
		this->camera->pos_x_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_LEFT])	// left arrow
	{
		this->camera->neg_x_dir();
		return;
	}
	else					// camera not moving
	{
		this->camera->zero_dir();
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

	int xCoordinate = floor(X / this->tileMap->getTileSize()) + this->camera->x_pos;			// x coordinate of moused over tile
	int yCoordinate = floor(Y / this->tileMap->getTileSize()) + this->camera->y_pos;			// y coordinate of moused over tile

	for (int x = 0; x < this->camera->getVisibleXTiles() + this->camera->x_pos; x++)
	{
		for (int y = 0; y < this->camera->getVisibleYTiles() + this->camera->y_pos; y++)
		{
			this->tileMap->unselectTile(x, y);
		}
	}
	this->tileMap->selectTile(xCoordinate, yCoordinate);
}

void Gameplay::update() {
  writeToLogFile(this->logFile, "updating in gameplay");
  this->camera->update(this->tileMap->getTotalXTiles(), this->tileMap->getTotalYTiles());	// update camera
  setSelectedTile();
}

void Gameplay::render(SDL_Renderer* renderer) {
  // Print out camera position. Temporary for debugging
  std::cout << "cam x pos: " << this->camera->x_pos << std::endl;
	std::cout << "cam y pos: " << this->camera->y_pos << std::endl;

	SDL_RenderClear(renderer);

	for (int x = 0; x < this->camera->getVisibleXTiles(); x++)		// visible x tiles
	{
		for (int y = 0; y < this->camera->getVisibleYTiles(); y++)	// visible y tiles
		{
			int currentXPosition = x + this->camera->x_pos;
			int currentYPosition = y + this->camera->y_pos;
			SDL_RenderCopy(renderer, this->tileMap->getTileTexture(currentXPosition, currentYPosition), NULL, &(this->camera->destinationRect[x][y]));	// render all visible tiles

			if (this->tileMap->getSelected(currentXPosition, currentYPosition)) {
				SDL_RenderCopy(renderer, this->selectedTexture, NULL, &(camera->destinationRect[x][y]));		// render selected texture over it
			}
		}
	}
  //this->testButton->render(renderer);
	SDL_RenderPresent(renderer);
}

void Gameplay::enterGameplay(int screenHeight, int screenWidth, SDL_Renderer* renderer) {
  // Initialize the camera
  writeToLogFile(this->logFile, "Initializing camera");
  this->camera = std::make_unique<Camera>(screenHeight, screenWidth, 16);
  assert(this->camera->getScreenHeight() == screenHeight);
  assert(this->camera->getScreenWidth() == screenWidth);
  this->camera->zoomChange(16);
  writeToLogFile(this->logFile, "Camera initialized");

  // Initialize the tile map
  writeToLogFile(this->logFile, "Initializing tile map...");
  this->tileMap = std::make_unique<TileMap>(16, 200, 200, renderer);
  writeToLogFile(this->logFile, "Tile map initialized");

  initializeTextures(renderer);

  // State has been entered once
  this->stateEntered = true;
}

void Gameplay::initializeTextures(SDL_Renderer* renderer) {
  writeToLogFile(logFile, "Initializing textures...");
	SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
	selectedTexture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
  writeToLogFile(logFile, "Textures initialized");
}

bool Gameplay::getStateEntered() {
  return this->stateEntered;
}
