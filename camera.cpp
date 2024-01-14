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
