#ifndef ONE_TILE_H
#define ONE_TILE_H 

#include "tile.h"

class OneTile : public Tile
{
	public:
		OneTile(SDL_Renderer*);
		~OneTile();
		void print();
};

#endif
