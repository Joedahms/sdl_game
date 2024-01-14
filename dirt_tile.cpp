#include <iostream>

#include "tile.h"
#include "dirt_tile.h"

DirtTile::DirtTile(SDL_Renderer* renderer)
{
	SDL_Surface* tmp_surface = IMG_Load("dirt_tile.png");
	this->tile_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

DirtTile::~DirtTile()
{

}

void DirtTile::print()
{
	std::cout << "dirt tile" << std::endl;
}
