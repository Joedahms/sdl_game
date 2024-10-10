#include <memory>
#include <vector>

#include "tile/tile.h"
#include "tile_map.h"

// Pass tile size
TileMap::TileMap(int tileSize, int totalXTiles, int totalYTiles, SDL_Renderer* renderer) {
	this->totalXTiles = totalXTiles;
	this->totalYTiles = totalYTiles;
	this->tileSize = tileSize;

	tile_vec.resize(totalXTiles);
	int random_num;			
	for (int x = 0; x < totalXTiles; x++)	// create tiles
	{
		for (int y = 0; y < totalYTiles; y++)
		{
			random_num = rand() % 2 + 1;	// random tile (either one or two)
			switch (random_num)		// which tile to add
			{
				case 1:		// one tile
					{
					std::unique_ptr<Tile> tile = tile_factory->create(tile_id::WATER_TILE, renderer);
					tile_vec[x].emplace_back(std::move(tile));
					break;
					}
				case 2:		// two tile
					{
					std::unique_ptr<Tile> tile = tile_factory->create(tile_id::DIRT_TILE, renderer);
					tile_vec[x].emplace_back(std::move(tile));
					break;
					}
				default:
					break;
			}	
		}
	}
	// Initialize tile_vec
}

void TileMap::setTileSize(int newTileSize) {
	tileSize = newTileSize;
}

int TileMap::getTileSize() {
	return tileSize;
}

void TileMap::selectTile(int xCoordinate, int yCoordinate) {
	tile_vec[xCoordinate][yCoordinate]->setSelected();
}

void TileMap::unselectTile(int xCoordinate, int yCoordinate) {
	tile_vec[xCoordinate][yCoordinate]->unsetSelected();
}

SDL_Texture* TileMap::getTileTexture(int xCoordinate, int yCoordinate) {
	return tile_vec[xCoordinate][yCoordinate]->getTileTexture();
}

bool TileMap::getSelected(int xCoordinate, int yCoordinate) {
	return tile_vec[xCoordinate][yCoordinate]->getSelected();
}

int TileMap::getTotalXTiles() {
	return totalXTiles;
}

int TileMap::getTotalYTiles() {
	return totalYTiles;
}
