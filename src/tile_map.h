#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>

#include "tile/tile_factory.h"

class TileMap {
  public:
    TileMap(int, int, int, SDL_Renderer*);
		void setTileSize(int);
		int getTileSize();
		void selectTile(int, int);
		void unselectTile(int, int);
		SDL_Texture* getTileTexture(int, int);
		bool getSelected(int, int);
		int getTotalXTiles();
		int getTotalYTiles();


	private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tileVector;
    std::unique_ptr<TileFactory> tile_factory = std::make_unique<TileFactory>();
  
		// Total number of tiles on each axis
		int totalXTiles;
		int totalYTiles;

		int tileSize;
};

#endif
