#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
  public:
  Button(int, int, int, int, const std::string&, TTF_Font*);

  std::string text; 
  std::string logFile;

  SDL_Rect rect; 
  SDL_Color color; 
  bool hovered;
  TTF_Font* font;

  bool checkHovered(const SDL_Event&);
  bool checkPressed(const SDL_Event&);

  void render(SDL_Renderer*);
};
