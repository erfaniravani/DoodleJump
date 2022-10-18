#ifndef _HOLE_HPP
#define _HOLE_HPP "_HOLE_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"

class Hole{
public:
	Hole(int hole_x , int hole_y);
	void hole_draw(Window* window);
	Point get_position();
	void set_position(Point pos);
private:
	Point position;
};

#endif