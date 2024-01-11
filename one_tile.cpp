#include <iostream>

#include "tile.h"
#include "one_tile.h"

OneTile::OneTile(SDL_Renderer* renderer)
{
	SDL_Surface* tmp_surface = IMG_Load("test_tile.png");
	this->tile_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

OneTile::~OneTile()
{

}

void OneTile::print()
{
	std::cout << "one tile" << std::endl;
}
