#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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

		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
		if (window)
		{
			std::cout << "window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}

		cam_x_tiles = width / tile_size;	// how many x tiles in view
		cam_y_tiles = height / tile_size;	// how many y tiles in view

		total_x_tiles = cam_x_tiles * 5;	// total x tiles
		total_y_tiles = cam_y_tiles * 5;	// total y tiles

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		
		// set up rectangles for rendering
		for (int x = 0; x < cam_x_tiles; x++)
		{
			for (int y = 0; y < cam_y_tiles; y++)
			{
				dest_rect[x][y].x = x*tile_size;	// x position
				dest_rect[x][y].y = y*tile_size;	// y position
				dest_rect[x][y].w = tile_size;		// width
				dest_rect[x][y].h = tile_size;		// height
			}
		}

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
						std::unique_ptr<Tile> tile = tile_factory->create(tile_id::ONE_TILE, renderer);
						tile_vec[x].emplace_back(std::move(tile));
						break;
						}
					case 2:		// two tile
						{
						std::unique_ptr<Tile> tile = tile_factory->create(tile_id::TWO_TILE, renderer);
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

void game::handle_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		std::cout << "event" << std::endl;
		switch (event.type)
		{
			case SDL_QUIT:
				std::cout << "quit" << std::endl;
				is_running = false;
				return;
		}
	}

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
		cam_y_dir = -1;
		return;
	}
	else if (keystates[SDL_SCANCODE_DOWN])	// down arrow
	{
		cam_y_dir = 1;
		return;
	}
	else if (keystates[SDL_SCANCODE_RIGHT])	// right arrow
	{
		cam_x_dir = 1;
		return;
	}
	else if (keystates[SDL_SCANCODE_LEFT])	// left arrow
	{
		cam_x_dir = -1;
		return;
	}
	else
	{
		cam_x_dir = 0;
		cam_y_dir = 0;	
	}
}

void game::update()
{
	current_ticks = SDL_GetTicks();


	delta_time = current_ticks - prev_ticks;
	total_delta_time += delta_time;	
	prev_ticks = current_ticks;

	std::cout << current_ticks << std::endl;

	if (total_delta_time >= 128)
	{
		total_delta_time = 0;
		cam_x_velocity = cam_x_dir * 1;
		cam_x_position += cam_x_velocity; //* delta_time;

		if (cam_x_position < 0)
		{
			cam_x_position = 0;
		}
		if (cam_x_position > total_x_tiles / 2)
		{
			cam_x_position = total_x_tiles / 2;
		}

		cam_y_velocity = cam_y_dir * 1;
		cam_y_position += cam_y_velocity; // * delta_time;

		if (cam_y_position < 0)
		{
			cam_y_position = 0;
		}
		if (cam_y_position > total_y_tiles / 2)
		{
			cam_y_position = total_y_tiles / 2;
		}
	}
}

void game::render()
{
	SDL_RenderClear(renderer);
	
	for (int x = 0; x < cam_x_tiles; x++)
	{
		for (int y = 0; y < cam_y_tiles; y++)
		{
			SDL_RenderCopy(renderer, tile_vec[x + cam_x_position][y + cam_y_position]->tile_texture, NULL, &dest_rect[x][y]);
		}
	}
	SDL_RenderPresent(renderer);
}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
