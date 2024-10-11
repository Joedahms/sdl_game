#include "camera.h"

Camera::Camera(int screenHeight, int screenWidth, int initialTileSize)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	zoomChange(initialTileSize);	
}

int Camera::getVisibleXTiles() {
	return visibleXTiles;
}

int Camera::getVisibleYTiles() {
	return visibleYTiles;
}

int Camera::get_x_dir()
{
	return x_dir;
}

int Camera::get_y_dir()
{
	return y_dir;
}

void Camera::neg_x_dir()
{
	x_dir = -1;
}

void Camera::pos_x_dir()
{
	x_dir = 1;
}

void Camera::neg_y_dir()
{
	y_dir = -1;
}

void Camera::pos_y_dir()
{
	y_dir = 1;
}

void Camera::zero_dir()
{
	x_dir = 0;
	y_dir = 0;
}

// move camera position for zoom in
void Camera::zoomIn(int tileSize) {
	x_pos += visibleXTiles / 4;
	y_pos += visibleYTiles / 4;

	zoomChange(tileSize);
}

// move camera position for zoom out
void Camera::zoomOut(int tileSize) {
	x_pos -= visibleXTiles / 2;
	if (x_pos < 0)			// x position past left side of map
	{
		x_pos = 0;
	}

	y_pos -= visibleYTiles / 2;
	if (y_pos < 0)			// y position past top of map
	{
		y_pos = 0;
	}

	zoomChange(tileSize);
}

void Camera::zoomChange(int tileSize) {
	// add to camera
	// set size of 2d vector of destination rectangles
	destinationRect.resize(screenWidth / tileSize, std::vector<SDL_Rect>(screenHeight / tileSize));	

	// set amount of tiles visible in window
	this->visibleXTiles = screenWidth / tileSize;	
	this->visibleYTiles = screenHeight / tileSize;
	
	// set up rectangles for rendering
	for (int x = 0; x < this->visibleXTiles; x++) {
		for (int y = 0; y < this->visibleYTiles; y++) {
			destinationRect[x][y].x = x*tileSize;	// x position
			destinationRect[x][y].y = y*tileSize;	// y position
			destinationRect[x][y].w = tileSize;		// width
			destinationRect[x][y].h = tileSize;		// height
		}
	}
}

void Camera::update(int total_x_tiles, int total_y_tiles)
{
	x_vel = get_x_dir() * 1;				// camera x velocity
	x_pos += x_vel; 					// camera x position

	if (x_pos < 0)						// left side of map
	{
		x_pos = 0;
	}
	// if camera x pos + visible x tiles is greater than total x tiles
	// then camera x pos = total x tiles - visible x tiles
	if (x_pos + visibleXTiles > total_x_tiles)		// right side of map
	{
		x_pos = total_x_tiles - visibleXTiles;
	}

	y_vel = get_y_dir() * 1;				// camera y velocity
	y_pos += y_vel; 					// camera y position

	if (y_pos < 0)						// left side of map
	{
		y_pos = 0;
	}
	if (y_pos + visibleYTiles > total_y_tiles)		// right side of map
	{
		y_pos = total_y_tiles - visibleYTiles;
	}
}

SDL_Rect & Camera::getDestinationRect(int xCoordinate, int yCoordinate) {
	return destinationRect[xCoordinate][yCoordinate];
}
