#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <memory>

#include "tile.h"

// factory for character objects
class TileFactory {
	public:
		std::unique_ptr<Tile> create(tile_id id, SDL_Renderer*);
};

#endif
