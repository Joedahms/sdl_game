#include "character.h"

// update position
void Character::update_y_pos()
{
	this->y_pos = this->y_pos += this->y_vel;
}

void Character::update_x_pos()
{
	this->x_pos = this->x_pos += this->x_vel;
}

// get position
int Character::get_y_pos()
{
	return this->y_pos;
}

int Character::get_x_pos()
{
	return this->x_pos;
}

// set velocity
void Character::set_y_vel(int new_y_vel)
{
	this->y_vel = new_y_vel;
}

void Character::set_x_vel(int new_x_vel)
{
	this->x_vel = new_x_vel;
}
