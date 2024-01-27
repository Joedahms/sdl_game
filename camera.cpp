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

void Camera::zoom_in()
{
	x_pos += visible_x_tiles / 4;
	y_pos += visible_y_tiles / 4;
}

void Camera::zoom_out()
{
	x_pos -= visible_x_tiles / 2;
	if (x_pos < 0)
	{
		x_pos = 0;
	}
	y_pos -= visible_y_tiles / 2;
	if (y_pos < 0)
	{
		y_pos = 0;
	}

}
