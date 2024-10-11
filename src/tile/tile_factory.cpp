#include <memory>

#include "tile.h"
#include "tile_factory.h"
#include "water_tile.h"
#include "dirt_tile.h"

// factory for tile objects
std::unique_ptr<Tile> TileFactory::create(tile_id id, SDL_Renderer* renderer)	
{
	if (tile_id::WATER_TILE == id)			
	{
		return std::make_unique<WaterTile>(renderer);
	}
	if (tile_id::DIRT_TILE == id)			
	{
		return std::make_unique<DirtTile>(renderer);
	}
	return nullptr;
}
