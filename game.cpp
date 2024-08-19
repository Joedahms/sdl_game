#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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
void game::initializeGame(const char* windowTitle, int windowXPosition, int windowYPosition, int screenWidth, int screenHeight, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initialized" << std::endl;

		// Window
		window = SDL_CreateWindow(windowTitle, windowXPosition, windowYPosition, screenWidth, screenHeight, flags);
		if (window)
		{
			std::cout << "window created" << std::endl;
		}

		// Renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		
		initializeTextures();	

		// Tilemap
		tileMap = std::make_unique<TileMap>(16, 1000, 1000, renderer);

		// Camera
		camera = std::make_unique<Camera>(screenHeight, screenWidth, 16);
		camera->zoomChange(16);

		// Create and initialize main menu
		mainMenu = std::make_unique<MainMenu>(renderer);

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		
		prev_ticks = SDL_GetTicks();	// first physics tick count
		gameIsRunning = true;
	}
	else 
	{
		gameIsRunning = false;			
	}
}

/*
 * Name: initializeTextures
 * Purpose: Initialize game textures
 * Input: None
 * Output: None
 */ 
void game::initializeTextures()
{
	SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
	selectedTexure = SDL_CreateTextureFromSurface(renderer, tmp_surface);
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
	while (SDL_PollEvent(&event) != 0) {					// Event occured
		switch (event.type) {			
			case SDL_QUIT:			
				gameIsRunning = false;	
				return;
			case SDL_MOUSEWHEEL:					// Mousewheel event
				if (event.wheel.y > 0) {			// Scroll up zoom in
					if (tileMap->getTileSize() == 16) {
						zoom_in_flag = true;
						zoom_out_flag = false;

						tileMap->setTileSize(32);
						camera->zoomIn(32);	
					}
				}
				else if (event.wheel.y < 0) { 			// Scroll down zoom out
        				if (tileMap->getTileSize() == 32) {
						zoom_in_flag = false;
						zoom_out_flag = true;

						tileMap->setTileSize(16);
						camera->zoomOut(16);
					}	
				}
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
	mainMenu->draw(renderer);
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
