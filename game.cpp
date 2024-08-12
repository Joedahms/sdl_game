#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game.h"
#include "camera/camera.h"
#include "menu/main_menu.h"

game::game()
{

}

game::~game()
{

}

void game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initialized" << std::endl;

		screen_width = width;
		screen_height = height;

		// create window
		window = SDL_CreateWindow(title, x_pos, y_pos, screen_width, screen_height, flags);
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

		// Create and initialize main menu
		mainMenu = std::make_unique<MainMenu>();
		mainMenu->init(renderer);

		// initializations dependent on tile size 
		init_ts_dependent();

		// total amount of tiles in game world
		total_x_tiles = camera->visible_x_tiles * 5;	
		total_y_tiles = camera->visible_y_tiles * 5;

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		
		tile_vec.resize(total_x_tiles);	// total x tiles
		int random_num;			
		for (int x = 0; x < total_x_tiles; x++)	// create tiles
		{
			for (int y = 0; y < total_y_tiles; y++)
			{
				random_num = rand() % 2 + 1;	// random tile (either one or two)
				switch (random_num)		// which tile to add
				{
					case 1:		// one tile
						{
						std::unique_ptr<Tile> tile = tile_factory->create(tile_id::WATER_TILE, renderer);
						tile_vec[x].emplace_back(std::move(tile));
						break;
						}
					case 2:		// two tile
						{
						std::unique_ptr<Tile> tile = tile_factory->create(tile_id::DIRT_TILE, renderer);
						tile_vec[x].emplace_back(std::move(tile));
						break;
						}
					default:
						break;
				}	
			}
		}
		prev_ticks = SDL_GetTicks();	// first physics tick count
		is_running = true;			// game is running
	}
	else 
	{
		is_running = false;			
	}
}

// initializations dependent on tile size
// seperate from init to allow for camera zooming
void game::init_ts_dependent()
{
	// set size of 2d vector of destination rectangles
	dest_rect.resize(screen_width / tile_size, std::vector<SDL_Rect>(screen_height / tile_size));	

	// set amount of tiles visible in window
	camera->visible_x_tiles = screen_width / tile_size;	
	camera->visible_y_tiles = screen_height / tile_size;
	
	// set up rectangles for rendering
	for (int x = 0; x < camera->visible_x_tiles; x++)
	{
		for (int y = 0; y < camera->visible_y_tiles; y++)
		{
			dest_rect[x][y].x = x*tile_size;	// x position
			dest_rect[x][y].y = y*tile_size;	// y position
			dest_rect[x][y].w = tile_size;		// width
			dest_rect[x][y].h = tile_size;		// height
		}
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
					if (tile_size == 16)
					{
						zoom_in_flag = true;
						zoom_out_flag = false;

						tile_size = 32;		// set new tile size
						camera->zoom_in();	// zoom in (change cam x and y)
						init_ts_dependent();	// change vars dependent on tile size
					}
				}
				else if (event.wheel.y < 0) // scroll down zoom out
				{
        				if (tile_size == 32)
					{
						zoom_in_flag = false;
						zoom_out_flag = true;

						tile_size = 16;		// set new tile size
						camera->zoom_out();	// zoom out (change cam x and y)
						init_ts_dependent();	// change vars dependent on tile size
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
	Uint32 mouse = SDL_GetMouseState(&X, &Y);	// see where mouse is

	int x_coord = floor(X / tile_size) + camera->x_pos;			// x coordinate of moused over tile
	int y_coord = floor(Y / tile_size) + camera->y_pos;			// y coordinate of moused over tile

	for (int x = 0; x < camera->visible_x_tiles + camera->x_pos; x++)
	{
		for (int y = 0; y < camera->visible_y_tiles + camera->y_pos; y++)
		{
			//tile_vec[x][y]->selected = false;
			tile_vec[x][y]->unsetSelected();
		}
	}

//	tile_vec[x_coord][y_coord]->selected = true;	// set moused over tile as selected
	tile_vec[x_coord][y_coord]->setSelected();

}

void game::update()
{
	current_ticks = SDL_GetTicks();	

	delta_time = current_ticks - prev_ticks;		// calc delta time from ticks
	total_delta_time += delta_time;				// num used to check if time to update
	prev_ticks = current_ticks;				// set prev ticks

	if (total_delta_time >= 128)				// update if it is time
	{
		total_delta_time = 0;				// reset counter
		camera->update(total_x_tiles, total_y_tiles);	// update camera
		set_selected_tile();
	}
}

void game::render()
{
	std::cout << "cam x pos: " << camera->x_pos << std::endl;
	std::cout << "cam y pos: " << camera->y_pos << std::endl;
	SDL_RenderClear(renderer);


	/*
	SDL_Surface* surface =  SDL_CreateRGBSurface(0,3,3,32,0,0,0,0);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 100;
	rect.h = 100;
*/


	for (int x = 0; x < camera->visible_x_tiles; x++)		// visible x tiles
	{
		for (int y = 0; y < camera->visible_y_tiles; y++)	// visible y tiles
		{
			auto & curr_tile = tile_vec[x + camera->x_pos][y + camera->y_pos];	// curr_tile

			SDL_RenderCopy(renderer, curr_tile->getTileTexture(), NULL, &dest_rect[x][y]);	// render all visible tiles

			if (curr_tile->getSelected())							// if selected
			{
				SDL_RenderCopy(renderer, selected_tex, NULL, &dest_rect[x][y]);		// render selected texture over it
			}
		}
	}
	mainMenu->draw(renderer);
	//SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_RenderPresent(renderer);
}

void game::clean()
{
	SDL_DestroyWindow(window);
//	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
