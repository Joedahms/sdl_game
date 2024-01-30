#ifndef GAME_H
#define GAME_H

// SDL
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <vector>
#include <memory>

#include "character.h"
#include "character_factory.h"
#include "player.h"
#include "npc.h"

#include "tile.h"
#include "tile_factory.h"
#include "water_tile.h"
#include "dirt_tile.h"

#include "camera.h"

class game
{
	public:
		game();
		~game();

		void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
		void init_ts_dependent();
		void init_textures();
		void handle_events();
		void check_keystates();
		void set_selected_tile();
		void update();
		void render();
		void clean();

		bool running() { return is_running; }

	private:
		bool is_running = false;	// if game is running

		int tile_size = 16;		// zoomed out

		std::unique_ptr<CharacterFactory> character_factory = std::make_unique<CharacterFactory>();	// character factory
	 	std::unique_ptr<TileFactory> tile_factory = std::make_unique<TileFactory>();	// tile factory

		std::vector<std::unique_ptr<Character>> player_vec;	// player vector
		std::vector<std::unique_ptr<Character>> npc_vec;	// npc vector
		
		std::vector<std::vector<std::unique_ptr<Tile>>> tile_vec; // tile map
		std::vector<std::vector<SDL_Rect>> dest_rect;	// needs to be dependent on screen size

		SDL_Texture* selected_tex;	// texture for selected tile

		SDL_Window* window;		// window
		SDL_Renderer* renderer;		// renderer

		std::unique_ptr<Camera> camera = std::make_unique<Camera>();	// camera
		
		// used in update
		int delta_time = 0;
		int total_delta_time = 0;

		// used in update
		Uint32 current_ticks;	
		Uint32 prev_ticks;

		// set in init
		int total_x_tiles;	
		int total_y_tiles;

		// screen dimensions
		int screen_width;
		int screen_height;

		// zoom flags
		// game starts zoomed out
		bool zoom_in_flag = false;
		bool zoom_out_flag = true;
		

};

#endif

