#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL_image.h>

enum tile_id { ONE_TILE, TWO_TILE };

class Tile
{
	public:
		virtual void print() = 0;
		//Tile(SDL_Renderer*);
		virtual ~Tile() = default;
		
		SDL_Texture* tile_texture;
	private:
};

#endif
