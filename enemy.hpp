#ifndef _ENEMY_HPP
#define _ENEMY_HPP "_ENEMY_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"


class Enemy
{
public:
	Enemy(int enemy_x , int enemy_y);
	void enemy_draw(Window* window);
	Point get_position();
	void set_position(Point p);
private:
	Point position;
};


#endif