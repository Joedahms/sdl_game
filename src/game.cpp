#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <assert.h>

#include "game.h"
#include "camera/camera.h"
#include "menu/main_menu.h"
#include "tile_map.h"


/*
 * Name: initializeGame
 * Purpose: Setup the game object
 * Input:
 * - Title of game window
 * - Window X Position
 * - Window Y Position
 * - Width of the screen
 * - Height of the screen
 * - Whether or not the game is fullscreen
 * Output: None
 */
void game::initializeGame(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen, std::string logFile) {
  this->logFile = logFile;
  this->window = setupWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, fullscreen);

  // Initialize SDL
  try {
    int sdlInitReturn = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdlInitReturn != 0) {
      throw;
    }
  }
  catch (...) {
    std::cout << "Failed to initialize SDL" << std::endl;
  }

  // Create renderer
  try {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
      throw;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  }
  catch (...) {
    std::cout << "Error creating renderer" << std::endl;
  }

  initializeTextures();
  
  // Initialize TTF
  try {
    int ttfInitReturn = TTF_Init();
    if (ttfInitReturn == -1) {
      throw;
    }
  }
  catch (...) {
    std::cout << "Failed to initialize TTF" << std::endl;
  }

  TTF_Font* font = TTF_OpenFont("../16020_FUTURAM.ttf", 24);
  if (font == NULL) {
    std::cout << TTF_GetError() << std::endl;
  }
  SDL_Color textColor = {255, 255, 255, 255}; // White color
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", textColor);
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  int textWidth, textHeight;
  SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect renderQuad = { 100, 100, textWidth, textHeight }; // Set position and size
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

  SDL_RenderPresent(renderer);

  button = std::make_unique<Button>(200, 150, 200, 50, "click", font);
  button->logFile = logFile;
  
  // Initialize the tile map
  tileMap = std::make_unique<TileMap>(16, 200, 200, renderer);
  
  // Initialize the camera
  camera = std::make_unique<Camera>(screenHeight, screenWidth, 16);
  assert(camera->getScreenHeight() == screenHeight);
  assert(camera->getScreenWidth() == screenWidth);
  camera->zoomChange(16);
  

  // Create and initialize main menu
  //mainMenu = std::make_unique<MainMenu>(renderer);

  // use factory to create objects here
  //std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
  //player_vec.emplace_back(std::move(player));
  //player_vec[0]->print();
  //player->print();
  
  prev_ticks = SDL_GetTicks();	// first physics tick count
  gameIsRunning = true;
}

SDL_Window* game::setupWindow(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen) {
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
    std::cout << "Window setup error" << std::endl;
    exit(1);
  }
}

/*
 * Name: initializeTextures
 * Purpose: Initialize game textures
 * Input: None
 * Output: None
 */ 
void game::initializeTextures() {
	SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
	selectedTexture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

/*
 * Name: handleEvents
 * Purpose: Check if SDL event has occured and handle accordingly
 * Input: None
 * Output: None
 */
void game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {    // SDL event occured
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
        button->checkHovered(event);
        break;

      case SDL_MOUSEBUTTONDOWN:
        button->checkPressed(event);
        break;

      default:
        break;
		}
	}
}

/*
 * Name: checkKeystates
 * Purpose: Perform desired action(s) depending on which key is pressed
 * Input: None
 * Output: None
 */
void game::checkKeystates()
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
	if (keystates[SDL_SCANCODE_UP])		// up arrow
	{
		camera->neg_y_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_DOWN])	// down arrow
	{
		camera->pos_y_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_RIGHT])	// right arrow
	{
		camera->pos_x_dir();
		return;
	}
	else if (keystates[SDL_SCANCODE_LEFT])	// left arrow
	{
		camera->neg_x_dir();
		return;
	}
	else					// camera not moving
	{
		camera->zero_dir();
	}
}

/* Name: setSelectedTile
 * Purpose: Determines where the mouse is and sets the tile it is over to selected
 * Input: None
 * Output: None
 */
void game::setSelectedTile() {
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

/*
 * Name: update
 * Purpose: Execute actions every game loop
 * Input: None
 * Output: None
 */
void game::update() {
	current_ticks = SDL_GetTicks();	

	delta_time = current_ticks - prev_ticks;		// calc delta time from ticks
	total_delta_time += delta_time;				// num used to check if time to update
	prev_ticks = current_ticks;				// set prev ticks

	if (total_delta_time >= 128)				// update if it is time
	{
		total_delta_time = 0;				// reset counter
		camera->update(tileMap->getTotalXTiles(), tileMap->getTotalYTiles());	// update camera
		setSelectedTile();
	}
}

/*
 * Name: render
 * Purpose: Either renders textures directly or calls functions to render
 * Input: None
 * Output: None
 */
void game::render() {
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
	//mainMenu->draw(renderer);
  button->render(renderer);
	SDL_RenderPresent(renderer);
}

/*
 * Name: clean
 * Purpose: Frees SDL resources and quits
 * Input: None
 * Output: None
 */
void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
