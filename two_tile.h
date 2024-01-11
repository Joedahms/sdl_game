#ifndef TWO_TILE_H
#define TWO_TILE_H 

#include "tile.h"

class TwoTile : public Tile
{
	public:
		TwoTile(SDL_Renderer*);
		~TwoTile();
		void print();
};

#endif
