#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game.h"
#include "camera.h"

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

		// initialize visible tiles
		init_vis_tiles();

		/*
		// set size of 2d vector of destination rectangles
		dest_rect.resize(width / tile_size, std::vector<SDL_Rect>(height / tile_size));	

		// set amount of tiles visible in window
		camera->visible_x_tiles = width / tile_size;	
		camera->visible_y_tiles = height / tile_size;
		*/

		// total amount of tiles in game world
		total_x_tiles = camera->visible_x_tiles * 5;	
		total_y_tiles = camera->visible_y_tiles * 5;

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		
		/*
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
		*/

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

void game::init_vis_tiles()
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

void game::init_textures()
{
	SDL_Surface* tmp_surface = IMG_Load("selected.png");
	selected_tex = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

void game::handle_events()
{

	std::cout << "before handle events" << tile_size << std::endl;
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				is_running = false;
				return;
			case SDL_MOUSEWHEEL:
				if(event.wheel.y > 0) // scroll up
		 		{
					if (tile_size == 16)
					{
						tile_size = 32;
						init_vis_tiles();
					}
				}
				else if(event.wheel.y < 0) // scroll down
				{
        				if (tile_size == 32)
					{
						tile_size = 16;
						init_vis_tiles();
					}	
				}
		}
	}

	std::cout << "after handle events" << tile_size << std::endl;


	//else if (event.type == SDL_KEYDOWN)	// keydown
	//{
		//switch (event.key.keysym.sym)
		//{
	//		default:
	//			break;	
	//	}
	//}
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
	else
	{
		camera->zero_dir();
	}
	std::cout << "check keystates" << std::endl;
}

void game::update()
{
	current_ticks = SDL_GetTicks();				// current ticks

	delta_time = current_ticks - prev_ticks;		// calc delta time from ticks
	total_delta_time += delta_time;				// num used to check if time to update
	prev_ticks = current_ticks;				// set prev ticks

	if (total_delta_time >= 128)				// update if its time
	{
		total_delta_time = 0;				// reset counter
		camera->x_vel = camera->get_x_dir() * 1;	// camera x velocity
		camera->x_pos += camera->x_vel; 		// camera x position

		if (camera->x_pos < 0)				// left side of map
		{
			camera->x_pos = 0;
		}
		if (camera->x_pos > total_x_tiles / 2)		// right side of map
		{
			camera->x_pos = total_x_tiles / 2;
		}

		camera->y_vel = camera->get_y_dir() * 1;	// camera y velocity
		camera->y_pos += camera->y_vel; 		// camera y position

		if (camera->y_pos < 0)				// left side of map
		{
			camera->y_pos = 0;
		}
		if (camera->y_pos > total_y_tiles / 2)		// right side of map
		{
			camera->y_pos = total_y_tiles / 2;
		}

		// selected stuff
		int X; 
		int Y;
		Uint32 mouse = SDL_GetMouseState(&X, &Y);	// see where mouse is

		int x_coord = floor(X / 16);			// x coordinate of moused over tile
		int y_coord = floor(Y / 16);			// y coordinate of moused over tile


		for (int x = 0; x < camera->visible_x_tiles; x++)
		{
			for (int y = 0; y < camera->visible_y_tiles; y++)
			{
				tile_vec[x][y]->selected = false;
			}
		}

		tile_vec[x_coord][y_coord]->selected = true;	// set moused over tile as selected
	}
	std::cout << "update" << std::endl;
}

void game::render()
{
	SDL_RenderClear(renderer);
	std::cout << camera->visible_x_tiles << std::endl;
	std::cout << camera->visible_y_tiles << std::endl;
	
	for (int x = 0; x < camera->visible_x_tiles; x++)		// visible x tiles
	{
		std::cout << "x" << x << std::endl;
		for (int y = 0; y < camera->visible_y_tiles; y++)	// visible y tiles
		{
			auto & curr_tile = tile_vec[x + camera->x_pos][y + camera->y_pos];	// curr_tile
			std::cout << "y" << y << std::endl;

			SDL_RenderCopy(renderer, curr_tile->tile_texture, NULL, &dest_rect[x][y]);	// render all visible tiles

			if (curr_tile->selected)							// if selected
			{
				SDL_RenderCopy(renderer, selected_tex, NULL, &dest_rect[x][y]);		// render selected texture over it
			}
		}
	}
	SDL_RenderPresent(renderer);
	std::cout << "render" << std::endl;
}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
