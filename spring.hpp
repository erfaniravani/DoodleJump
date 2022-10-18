#ifndef _SPRING_HPP
#define _SPRING_HPP "_SPRING_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"

class Spring{
public:
	Spring(int spring_x , int spring_y);
	void spring_draw(Window* window);
	Point get_position();
	void set_position(Point p);
	void set_on_spring(bool on);
private:
	Point position;
	bool on_spring;
	int frame_count;
};

#endif