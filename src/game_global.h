#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

#include <SDL2/SDL.h>
#include <string>

struct GameGlobal {
  std::string logFile;    // Path to the log file
  SDL_Renderer* renderer;
  SDL_Window* window;
};

#endif
