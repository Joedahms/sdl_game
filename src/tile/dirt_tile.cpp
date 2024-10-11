#include <iostream>
#include <assert.h>

#include "tile.h"
#include "dirt_tile.h"

DirtTile::DirtTile(SDL_Renderer* renderer)
{
	SDL_Surface* temporarySurface = IMG_Load("../src/sprites/dirt_tile.png");
  assert(temporarySurface != 0);

	tileTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
  assert(tileTexture != 0);

	SDL_FreeSurface(temporarySurface);
}

void DirtTile::print()
{
	std::cout << "dirt tile" << std::endl;
}
