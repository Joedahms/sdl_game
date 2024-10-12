#include <SDL2/SDL.h>

#include <iostream>

#include "game.h"

game* game_obj = nullptr;

int main(int argc, const char* argv[])
{
	Uint64 frame_start;
	Uint64 frame_end;
	float elapsedMS;

	game_obj = new game();
	game_obj->initializeGame("game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false);

	while (game_obj->running())
	{
		int X; 
		int Y;
		Uint32 mouse = SDL_GetMouseState(&X, &Y);

		frame_start = SDL_GetPerformanceCounter();

		game_obj->handleEvents();
		game_obj->checkKeystates();
		game_obj->update();

		game_obj->render();

		frame_end = SDL_GetPerformanceCounter();
		elapsedMS = (frame_end - frame_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	}
	
	game_obj->clean();

	return 0;
}
