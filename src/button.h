#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
public:
  SDL_Rect rect; 
  SDL_Color color; 
  bool hovered;
  std::string text; 
  TTF_Font* font;
  Button(int, int, int, int, const std::string&, TTF_Font*);
  void handleEvent(const SDL_Event&);
  void render(SDL_Renderer*);

  std::string logFile;

};
