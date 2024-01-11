#include <iostream>

#include "tile.h"
#include "two_tile.h"

TwoTile::TwoTile(SDL_Renderer* renderer)
{
	SDL_Surface* tmp_surface = IMG_Load("test_tile02.png");
	this->tile_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

TwoTile::~TwoTile()
{

}

void TwoTile::print()
{
	std::cout << "two tile" << std::endl;
}
