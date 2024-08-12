#ifndef WATER_TILE_H
#define WATER_TILE_H 

#include "tile.h"

class WaterTile : public Tile
{
	public:
		WaterTile(SDL_Renderer*);
		void print();
};

#endif
