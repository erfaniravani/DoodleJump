#ifndef _GAME_HPP
#define _GAME_HPP "_GAME_HPP"
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"
#include <vector>
#include <string>
#include "doodle.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include "inputfile.hpp"
#include "spring.hpp"
#include "hole.hpp"



class Spring;

class Game
{
public:
	int restart_game;
	Game(Window* _window , Doodle* _doodle);
	void draw_func(Window* window , std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes);
	void update_func(Window* window , std::vector<Platform*> platforms , std::vector<Enemy*> enemies , int& go_right , int& go_left ,
					 std::vector<Spring*> sp , std::vector<Hole*> holes);
private:
	int score;
	Window* window;
	Doodle* doodle;
	bool game_over;
	std::string game_over_reason;
	int update_camera(std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes);
	void update_score(int diff);
	void doodle_up();
	void doodle_down();
	void update_doodle_on_platform(std::vector<Platform*> platforms , Window* window);
	bool doodle_fall();
	void check_enemy(std::vector<Enemy*> enemies , Window* window);
	void check_holes(std::vector<Hole*> holes);
	void update_doodle_on_spring(std::vector<Spring*> sp);
	void update_camera_platform(std::vector<Platform*> platforms , int height_diff);
	void update_camera_enemy(std::vector<Enemy*> enemies , int height_diff);
	void update_camera_spring(std::vector<Spring*> sp , int height_diff);
	void update_camera_hole(std::vector<Hole*> holes , int height_diff);
	void update_camera_doodle(int height_diff);
	void draw_game_over();
	void update_doodle_left();
	void update_doodle_right();
	void update_game(std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes , Window* window);
	void draw_game();
	bool doodle_on_platform(Doodle* doodle  , Platform* platform);
	bool doodle_spring(Doodle* doodle , Spring* sp);
	bool doodle_on_enemy(Doodle* doodle , Enemy* enemy);
	bool doodle_on_hole(Doodle* doodle , Hole* holes);
	bool same_width_right_enemy(int entity_x_begin , int doodle_x);
	bool same_width_left_enemy(int entity_x_begin , int doodle_x);
	bool same_width_right_spring(int entity_x_begin , int doodle_x);
	bool same_width_left_spring(int entity_x_begin , int doodle_x);
	bool same_width_right_platform(int entity_x_begin , int doodle_x);
	bool same_width_left_platform(int entity_x_begin , int doodle_x);
	bool same_width_right_hole(int entity_x_begin , int doodle_x);
	bool same_width_left_hole(int entity_x_begin , int doodle_x);
	bool same_height_platform(int entity_x_begin , int doodle_h);
	bool same_height_spring(int spring_y_begin , int doodle_h);
	bool same_height_enemy(int enemy_h_begin , int doodle_h_begin);
	bool same_height_hole(int hole_h_begin , int doodle_h_begin);


};

#endif