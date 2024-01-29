#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

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
void Camera::zoom_in()
{
	x_pos += visible_x_tiles / 4;
	y_pos += visible_y_tiles / 4;
}

// move camera position for zoom out
void Camera::zoom_out()
{
	x_pos -= visible_x_tiles / 2;
	if (x_pos < 0)			// x position past left side of map
	{
		x_pos = 0;
	}
	y_pos -= visible_y_tiles / 2;
	if (y_pos < 0)			// y position past top of map
	{
		y_pos = 0;
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
	if (x_pos + visible_x_tiles > total_x_tiles)		// right side of map
	{
		x_pos = total_x_tiles - visible_x_tiles;
	}

	y_vel = get_y_dir() * 1;				// camera y velocity
	y_pos += y_vel; 					// camera y position

	if (y_pos < 0)						// left side of map
	{
		y_pos = 0;
	}
	if (y_pos + visible_y_tiles > total_y_tiles)		// right side of map
	{
		y_pos = total_y_tiles - visible_y_tiles;
	}
}
