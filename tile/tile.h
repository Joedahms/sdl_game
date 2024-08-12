#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL_image.h>

enum tile_id { WATER_TILE, DIRT_TILE };

class Tile {
	public:
		virtual void print() = 0;
		void setSelected();
		void unsetSelected();
		bool getSelected();
		SDL_Texture* getTileTexture();
		
	protected:
		SDL_Texture* tileTexture;
		bool selected = false;
};

#endif
