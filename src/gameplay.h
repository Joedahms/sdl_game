#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "tile/tile_map.h"
#include "camera/camera.h"
#include "game_global.h"

class Gameplay {
  public:
  Gameplay(struct GameGlobal);
  int handleEvents(bool*);                      // Handle SDL events
  void checkKeystates();                        // Check which keys on the keyboard are pressed
  void setSelectedTile();                       // Set the hovered tile as selected
  void update();
  void render();                                // Render to window
  void enterGameplay();                         // Set up upon first entry into state
  void initializeTextures();
  bool getStateEntered();                       // Check if the state has already been entered

  private:
  struct GameGlobal gameGlobal;                 // Global variables
  bool stateEntered = false;                    // Has the state been entered before

  std::unique_ptr<Camera> camera;               // Camera
  std::unique_ptr<TileMap> tileMap;             // Tile map
 
  // Zoom flags
  // Game starts zoomed out
  bool zoom_in_flag = false;
  bool zoom_out_flag = true;

  SDL_Texture* selectedTexture;                 // Texture for selected tile
};

#endif
