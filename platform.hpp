#ifndef _PLATFORM_HPP
#define _PLATFORM_HPP "_PLATFORM_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"

class Platform{
public:
	Platform(int platform_x , int platform_y);
	virtual Point get_position();
	virtual void update_position();
	virtual void platform_draw(Window* window);
	virtual bool get_breakable();
	virtual void set_broken(bool b);
	virtual void set_position(Point p);
	virtual bool get_broken();

protected:
	Point position;
	bool breakable;
	bool broken;
	int animate;
};

class Mplatform : public Platform{
public:
	Mplatform(int mplatform_x , int mplatform_y);
	virtual Point get_position();
	virtual void update_position();
	virtual void platform_draw(Window* window);
	virtual bool get_breakable();
	virtual void set_broken(bool b);
	virtual void set_position(Point p);
	virtual bool get_broken();
private:
	Point next_position;
	int reverse;

};

class Bplatform : public Platform{
public:
	Bplatform(int bplatform_x , int bplatform_y);
	virtual Point get_position();
	virtual void update_position();
	virtual void platform_draw(Window* window);
	virtual bool get_breakable();
	virtual void set_broken(bool b);
	virtual void set_position(Point p);
	virtual bool get_broken();

};


#endif