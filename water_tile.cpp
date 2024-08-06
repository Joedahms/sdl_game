#include <iostream>

#include "tile.h"
#include "water_tile.h"

WaterTile::WaterTile(SDL_Renderer* renderer)
{
	SDL_Surface* tmp_surface = IMG_Load("sprites/water_tile.png");
	this->tile_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

WaterTile::~WaterTile()
{

}

void WaterTile::print()
{
	std::cout << "water tile" << std::endl;
}
