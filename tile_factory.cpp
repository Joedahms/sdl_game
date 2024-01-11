#include <memory>

#include "tile.h"
#include "tile_factory.h"
#include "one_tile.h"
#include "two_tile.h"

// factory for tile objects
std::unique_ptr<Tile> TileFactory::create(tile_id id, SDL_Renderer* renderer)	
{
	if (tile_id::ONE_TILE == id)			
	{
		return std::make_unique<OneTile>(renderer);
	}
	if (tile_id::TWO_TILE == id)			
	{
		return std::make_unique<TwoTile>(renderer);
	}
	return nullptr;
}
