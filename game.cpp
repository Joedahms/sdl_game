#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game.h"
#include "camera/camera.h"
#include "menu/main_menu.h"
#include "tile_map.h"

void game::init(const char* title, int x_pos, int y_pos, int screenWidth, int screenHeight, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initialized" << std::endl;

		// create window
		window = SDL_CreateWindow(title, x_pos, y_pos, screenWidth, screenHeight, flags);
		if (window)
		{
			std::cout << "window created" << std::endl;
		}

		// create renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		
		// initialize textures
		init_textures();	

		tileMap = std::make_unique<TileMap>(16, 1000, 1000, renderer);
		camera = std::make_unique<Camera>(screenHeight, screenWidth, 16);
		camera->zoomChange(16);
		mainMenu = std::make_unique<MainMenu>(renderer);

		// Create and initialize main menu
		mainMenu = std::make_unique<MainMenu>(renderer);

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		prev_ticks = SDL_GetTicks();	// first physics tick count
		is_running = true;			// game is running
	}
	else 
	{
		is_running = false;			
	}
}

// tile textures initialized upon creation
void game::init_textures()
{
	SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
	selected_tex = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

void game::handle_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {		// got an event
		switch (event.type) {			// what is the event type
			case SDL_QUIT:			// quit event
				is_running = false;	// not running anymore
				return;
			case SDL_MOUSEWHEEL:		// mousewheel event
				if (event.wheel.y > 0)	// scroll up zoom in
		 		{
					if (tileMap->getTileSize() == 16)
					{
						zoom_in_flag = true;
						zoom_out_flag = false;

		//				tile_size = 32;		// set new tile size
						tileMap->setTileSize(32);
						camera->zoomIn(32);	// zoom in (change cam x and y)
//						init_ts_dependent();	// change vars dependent on tile size
					}
				}
				else if (event.wheel.y < 0) // scroll down zoom out
				{
        				if (tileMap->getTileSize() == 32)
					{
						zoom_in_flag = false;
						zoom_out_flag = true;

						//tile_size = 16;		// set new tile size
						tileMap->setTileSize(16);
						camera->zoomOut(16);	// zoom out (change cam x and y)
						//init_ts_dependent();	// change vars dependent on tile size
					}	
				}
		}
	}
}

void game::check_keystates()
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

void game::set_selected_tile()
{
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

void game::update() {
	current_ticks = SDL_GetTicks();	

	delta_time = current_ticks - prev_ticks;		// calc delta time from ticks
	total_delta_time += delta_time;				// num used to check if time to update
	prev_ticks = current_ticks;				// set prev ticks

	if (total_delta_time >= 128)				// update if it is time
	{
		total_delta_time = 0;				// reset counter
		camera->update(tileMap->getTotalXTiles(), tileMap->getTotalYTiles());	// update camera
		set_selected_tile();
	}
}

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
				std::cout << "selected" << std::endl;
				SDL_RenderCopy(renderer, selected_tex, NULL, &(camera->destinationRect[x][y]));		// render selected texture over it
			}
		}
	}
	//mainMenu->draw(renderer);
	SDL_RenderPresent(renderer);
}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
