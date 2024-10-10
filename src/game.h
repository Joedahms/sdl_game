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

#include "tile/tile.h"
#include "tile/tile_factory.h"
#include "tile/water_tile.h"
#include "tile/dirt_tile.h"

#include "camera/camera.h"

#include "menu/main_menu.h"

#include "tile_map.h"

class game {
	public:
		void initializeGame(const char*, int, int, int, int, bool);
		void initializeTextures();
		void handleEvents();
		void checkKeystates();
		void setSelectedTile();
		void update();
		void render();
		void clean();

		bool running() { return gameIsRunning; }

	private:
		bool gameIsRunning = false;

		std::unique_ptr<CharacterFactory> character_factory = std::make_unique<CharacterFactory>();

		std::unique_ptr<Menu> mainMenu;// = std::make_unique<MainMenu>(renderer);

		std::vector<std::unique_ptr<Character>> player_vec;	// player vector
		std::vector<std::unique_ptr<Character>> npc_vec;	// npc vector
		
		SDL_Texture* selectedTexture;	// texture for selected tile

		SDL_Window* window;		
		SDL_Renderer* renderer;	

		std::unique_ptr<Camera> camera;
		
		int delta_time = 0;
		int total_delta_time = 0;

		Uint32 current_ticks;	
		Uint32 prev_ticks;

		// zoom flags
		// game starts zoomed out
		bool zoom_in_flag = false;
		bool zoom_out_flag = true;

		// Tile map object
		std::unique_ptr<TileMap> tileMap;// = std::make_unique<TileMap>(16, 1000, 1000, renderer);
};

#endif

