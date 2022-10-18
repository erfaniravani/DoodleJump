#ifndef _DOODLE_HPP
#define _DOODLE_HPP "_DOODLE_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"
#include <string>

class Doodle
{
public:
	Doodle(int doodle_x , int doodle_y);
	void jump_up(double move);
	void jump_down(double move);
	void go_left(int move);
	void go_right(int move);
	void doodle_draw(Window* window);
	std::string get_todo();
	Point get_position();
	int get_jump_from();
	int get_jump_height();
	std::string get_face();
	std::string get_status();
	bool get_finish_game();
	void set_jump_height(int jh);
	void set_jump_from(int h);
	void set_todo(std::string up_down);
	void set_position(Point p);
	void set_status(std::string s);
	void set_count(int c);

private:
	Point position;
	std::string face;
	std::string to_do;
	int jump_from;
	int jump_height;
	std::string status;
	int frame;
	int count;
	bool finish_game;
	void draw_out_hole(Window* window);
	void draw_in_hole(Window* window);
	;
	
};



#endif