// Function comment template
/*
 * Name: 
 * Purpose:
 * Input:
 * Output:
*/

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "game.h"
#include "logger.h"
#include "game_global.h"

int main(int argc, const char* argv[]) {
  struct GameGlobal gameGlobal;
  gameGlobal.logFile = "../log.txt";      // Set the log file path
  clearLogFile(gameGlobal.logFile);                  // Remove contents of log file

	Uint64 frame_start;
	Uint64 frame_end;
	float elapsedMS;

  // Initialize the game
  std::unique_ptr<Game> game = std::make_unique<Game>("game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false, gameGlobal);

	while (game->running()) { // While the game is running
		game->handleEvents();
    game->checkState();
		game->checkKeystates();
		game->update();
		game->renderState();
	}
	game->clean();
	return 0;
}
