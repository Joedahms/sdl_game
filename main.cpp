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
	game_obj->init("game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false);

	while (game_obj->running())
	{
		int X; 
		int Y;
		Uint32 mouse = SDL_GetMouseState(&X, &Y);

		//std::cout << X << std::endl;
		//std::cout << Y << std::endl;

		frame_start = SDL_GetPerformanceCounter();

		game_obj->handle_events();
		game_obj->check_keystates();
		game_obj->update();
		game_obj->render();

		frame_end = SDL_GetPerformanceCounter();
		elapsedMS = (frame_end - frame_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		//SDL_Delay(abs(floor(16.666f - elapsedMS)));
		//SDL_Delay(floor(60 - elapsedMS));
	}
	
	game_obj->clean();

	return 0;
}
