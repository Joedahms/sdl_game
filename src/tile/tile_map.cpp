#include <iostream>
#include <memory>
#include <vector>

#include "tile.h"
#include "tile_map.h"

// Pass tile size
TileMap::TileMap(int tileSize, int totalXTiles, int totalYTiles, SDL_Renderer* renderer) {
	this->totalXTiles = totalXTiles;
	this->totalYTiles = totalYTiles;
	this->tileSize = tileSize;

	tileVector.resize(totalXTiles);
	int random_num;

  std::unique_ptr<Tile> waterTile;
  std::unique_ptr<Tile> dirtTile;

	for (int x = 0; x < totalXTiles; x++) {
		for (int y = 0; y < totalYTiles; y++) {
			random_num = rand() % 2 + 1;	// random tile (either one or two)

			switch (random_num) { // Which type of tile to add to the array
				case 1: // Water tile
          {
          std::unique_ptr<Tile> waterTile = tile_factory->create(tile_id::WATER_TILE, renderer);
					//waterTile = tile_factory->create(tile_id::WATER_TILE, renderer);
					tileVector[x].emplace_back(std::move(waterTile));
					break;
          }

				case 2: // Dirt tile
          {
          std::unique_ptr<Tile> dirtTile = tile_factory->create(tile_id::DIRT_TILE, renderer);
					//dirtTile = tile_factory->create(tile_id::DIRT_TILE, renderer);
					tileVector[x].emplace_back(std::move(dirtTile));
					break;
          }

				default:
          break;
			}
		}
	}
}

void TileMap::setTileSize(int newTileSize) {
	tileSize = newTileSize;
}

int TileMap::getTileSize() {
	return tileSize;
}

void TileMap::selectTile(int xCoordinate, int yCoordinate) {
	tileVector[xCoordinate][yCoordinate]->setSelected();
}

void TileMap::unselectTile(int xCoordinate, int yCoordinate) {
	tileVector[xCoordinate][yCoordinate]->unsetSelected();
}

SDL_Texture* TileMap::getTileTexture(int xCoordinate, int yCoordinate) {
	return tileVector[xCoordinate][yCoordinate]->getTileTexture();
}

bool TileMap::getSelected(int xCoordinate, int yCoordinate) {
	return tileVector[xCoordinate][yCoordinate]->getSelected();
}

int TileMap::getTotalXTiles() {
	return totalXTiles;
}

int TileMap::getTotalYTiles() {
	return totalYTiles;
}
