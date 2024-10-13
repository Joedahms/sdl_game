#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <string>

// Character
#include "character/character.h"
#include "character/character_factory.h"
#include "character/player.h"
#include "character/npc.h"

// Tile
#include "tile/tile.h"
#include "tile/tile_factory.h"
#include "tile/water_tile.h"
#include "tile/dirt_tile.h"

// Camera
#include "camera/camera.h"

#include "main_menu.h"
#include "gameplay.h"

class Game {
	public:
  Game(const char*, int, int, int, int, bool, std::string);       // Constructor

  SDL_Window* setupWindow(const char*, int, int, int, int, bool); // Setup the SDL game window
  void initializeSdl(SDL_Window*);

  void checkState();                                              // Check which state the game is in
  void handleEvents();                                            // Handle events depending on current state
  void checkKeystates();                                          // Check keyboard key presses depending on state
  void update();                                                  // Update game depending on state

  void renderState();                                             // Render the current state
  void clean();                                                   // Clean up upon quit
  bool running() { return gameIsRunning; }                        // Check if the game is running

	private:
  int screenHeight;                                               // Height of the screen in pixels
  int screenWidth;                                                // Width of the screen in pixels

  // State the game is currently in
  // 0: Main menu
  // 1: Gameplay
  // 2: Pause menu
  int state = 0;

  // States
  std::unique_ptr<MainMenu> mainMenu;                             // Main menu. State entered when the game starts
  std::unique_ptr<Gameplay> gameplay;                             // Game play. State the game is in when it is running

  bool gameIsRunning = false;                                     // If the game is running
  std::string logFile;                                            // Path to the log file

  std::unique_ptr<CharacterFactory> character_factory = std::make_unique<CharacterFactory>(); // Not currently used

  std::vector<std::unique_ptr<Character>> player_vec;             // Not currently used
  std::vector<std::unique_ptr<Character>> npc_vec;                // Not currently used

  SDL_Window* window;                                             // SDL game window
  SDL_Renderer* renderer;                                         // Renderer for rendering textures
  
  int deltaTime = 0;                                              // Time since last checked if game should update
  int totalDeltaTime = 0;                                         // Time since last update

  Uint32 currentTicks;                                            // Ticks at current update check
  Uint32 previousTicks;                                           // Ticks at the last update check
};

#endif

