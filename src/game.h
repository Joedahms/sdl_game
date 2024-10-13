#ifndef GAME_H
#define GAME_H

// SDL
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <vector>
#include <memory>
#include <string>

#include "character.h"
#include "character_factory.h"
#include "player.h"
#include "npc.h"

#include "tile/tile.h"
#include "tile/tile_factory.h"
#include "tile/water_tile.h"
#include "tile/dirt_tile.h"

#include "camera/camera.h"

#include "main_menu.h"
#include "gameplay.h"

class Game {
	public:
  Game(const char*, int, int, int, int, bool, std::string);

  SDL_Window* setupWindow(const char*, int, int, int, int, bool);

  void checkState();
  void handleEvents();
  void checkKeystates();
//  void setSelectedTile();
  void update();

  void renderState();

  void clean();

  bool running() { return gameIsRunning; }

	private:

  int screenHeight;
  int screenWidth;

  // State variables
  // 0: Main menu
  // 1: Gameplay
  // 2: Pause menu
  int state = 0;
  bool mainMenuStateInitialized = false;
  bool gameplayStateInitialized = false;
  bool pauseMenuStateInitialized = false;

  std::unique_ptr<MainMenu> mainMenu;
  std::unique_ptr<Gameplay> gameplay;

  bool gameIsRunning = false;
  std::string logFile;

  std::unique_ptr<CharacterFactory> character_factory = std::make_unique<CharacterFactory>();

  std::vector<std::unique_ptr<Character>> player_vec;   // Vector of players
  std::vector<std::unique_ptr<Character>> npc_vec;      // Vector of NPCs

  SDL_Window* window;
  SDL_Renderer* renderer;
  
  int delta_time = 0;
  int total_delta_time = 0;

  Uint32 current_ticks;	
  Uint32 prev_ticks;
};

#endif

