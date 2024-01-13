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
#include "one_tile.h"
#include "two_tile.h"

class game
{
	public:
		game();
		~game();

		void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
		void handle_events();
		void check_keystates();
		void update();
		void render();
		void clean();

		bool running() { return is_running; }

	private:
		bool is_running = false;

		std::unique_ptr<CharacterFactory> character_factory = std::make_unique<CharacterFactory>();	// character factory
		std::unique_ptr<TileFactory> tile_factory = std::make_unique<TileFactory>();	// tile factory

		std::vector<std::unique_ptr<Character>> player_vec;	// player vector
		std::vector<std::unique_ptr<Character>> npc_vec;	// npc vector
		
		std::vector<std::vector<std::unique_ptr<Tile>>> tile_vec; // tile map
		SDL_Rect dest_rect[25][20];	// needs to be dependent on screen size

		SDL_Window* window;
		SDL_Renderer* renderer;

		Uint32 last_physics_update;
		Uint32 curr_physics_update;
		float delta_time;

		int cam_x_dir = 0;
		int cam_y_dir = 0;

		int cam_x_position = 0;
		int cam_y_position = 0;

		int cam_x_velocity = 0;
		int cam_y_velocity = 0;

		int tile_size = 32;

		int cam_x_tiles;	// how many x tiles in view
		int cam_y_tiles;	// how many y tiles in view
		
		int total_x_tiles;	// total x tiles
		int total_y_tiles;	// total y tiles

};

#endif

