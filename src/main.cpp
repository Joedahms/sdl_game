#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "game.h"
#include "logger.h"

int main(int argc, const char* argv[])
{
  std::string logFile = "../log.txt";
  clearLogFile(logFile);

	Uint64 frame_start;
	Uint64 frame_end;
	float elapsedMS;

  std::unique_ptr<Game> game = std::make_unique<Game>("game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false, logFile);
//	game_obj->initializeGame("game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false, logFile);

	while (game->running())
	{
		int X; 
		int Y;
		Uint32 mouse = SDL_GetMouseState(&X, &Y);

		frame_start = SDL_GetPerformanceCounter();

		game->handleEvents();
		game->checkKeystates();
		game->update();
		game->render();

		frame_end = SDL_GetPerformanceCounter();
		elapsedMS = (frame_end - frame_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
	}
	
	game->clean();

	return 0;
}
