#include "tile.h"

void Tile::setSelected() {
	selected = true;
}

void Tile::unsetSelected() {
	selected = false;
}

bool Tile::getSelected() {
	return selected;
}

SDL_Texture* Tile::getTileTexture() {
	return tileTexture;	
}
