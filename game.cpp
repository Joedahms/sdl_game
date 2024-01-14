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

		//cam_x_tiles = width / tile_size;	// how many x tiles in view
		//cam_y_tiles = height / tile_size;	// how many y tiles in view
		camera->visible_x_tiles = width / tile_size;
		camera->visible_y_tiles = height / tile_size;

		total_x_tiles = camera->visible_x_tiles * 5;	// total x tiles based on cam
		total_y_tiles = camera->visible_y_tiles * 5;	// total y tiles based on cam

		// use factory to create objects here
		//std::unique_ptr<Character> player = character_factory->create(character_id::PLAYER);
		//player_vec.emplace_back(std::move(player));
		//player_vec[0]->print();
		//player->print();
		
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
		camera->x_vel = camera->get_x_dir() * 1;
		camera->x_pos += camera->x_vel; //* delta_time;

		if (camera->x_pos < 0)
		{
			camera->x_pos = 0;
		}
		if (camera->x_pos > total_x_tiles / 2)
		{
			camera->x_pos = total_x_tiles / 2;
		}

		camera->y_vel = camera->get_y_dir() * 1;
		camera->y_pos += camera->y_vel; // * delta_time;

		if (camera->y_pos < 0)
		{
			camera->y_pos = 0;
		}
		if (camera->y_pos > total_y_tiles / 2)
		{
			camera->y_pos = total_y_tiles / 2;
		}
	}
}

void game::render()
{
	SDL_RenderClear(renderer);
	
	for (int x = 0; x < camera->visible_x_tiles; x++)
	{
		for (int y = 0; y < camera->visible_y_tiles; y++)
		{
			SDL_RenderCopy(renderer, tile_vec[x + camera->x_pos][y + camera->y_pos]->tile_texture, NULL, &dest_rect[x][y]);
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
