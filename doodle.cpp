#include "doodle.hpp"

Doodle::Doodle(int doodle_x , int doodle_y){
	position = Point(doodle_x - (DOODLE_WIDTH/2) , HEIGHT - doodle_y - DOODLE_HEIGHT);
	jump_from = position.y;
	face = LEFT;
	to_do = UP;
	jump_height = JUMP_UP;
	status = REST;
	frame = 0;
	finish_game = false;
	count = 0;
}

void Doodle::go_left(int move){
	position = Point(position.x - move , position.y);
	face = LEFT;
	if(position.x + (DOODLE_WIDTH/2) < 0)
		position = Point(WIDTH - (DOODLE_WIDTH/2) , position.y);
}

void Doodle::go_right(int move){
	position = Point(position.x + move , position.y);
	face = RIGHT;
	if(position.x + (DOODLE_WIDTH/2) > WIDTH)
		position = Point(-DOODLE_WIDTH/2, position.y);
}
void Doodle::doodle_draw(Window* window){
	if(status != HOLE)
		draw_out_hole(window);
	else
		draw_in_hole(window);
}

void Doodle::draw_in_hole(Window* window){
	if(frame > HOLE_ANIMATION)
		finish_game = true;
	frame++;
	if(face == LEFT){
		if(position.y <= jump_from and position.y > jump_from - LEGS_ANIMATION and status == PLATFORM){
			window->draw_img(DOODLE_LEFT_JUMP, Rectangle(position.x , position.y , DOODLE_WIDTH - frame , DOODLE_HEIGHT - frame));
		}
		else{
			window->draw_img(DOODLE_IMAGE_LEFT, Rectangle(position.x , position.y , DOODLE_WIDTH - frame , DOODLE_HEIGHT - frame));
		}
	}
	else if(face == RIGHT){
		if(position.y <= jump_from and position.y > jump_from - LEGS_ANIMATION and status == PLATFORM){
			window->draw_img(DOODLE_RIGHT_JUMP, Rectangle(position.x , position.y , DOODLE_WIDTH - frame , DOODLE_HEIGHT - frame));
		}
		else{
			window->draw_img(DOODLE_IMAGE_RIGHT, Rectangle(position.x , position.y , DOODLE_WIDTH - frame , DOODLE_HEIGHT - frame));
		}
	}
}

void Doodle::draw_out_hole(Window* window){
	if(face == LEFT){
		if(position.y <= jump_from and position.y > jump_from - LEGS_ANIMATION){
			window->draw_img(DOODLE_LEFT_JUMP, Rectangle(position.x , position.y , DOODLE_WIDTH , DOODLE_HEIGHT));
		}
		else{
			window->draw_img(DOODLE_IMAGE_LEFT, Rectangle(position.x , position.y , DOODLE_WIDTH , DOODLE_HEIGHT));
		}
	}
	else if(face == RIGHT){
		if(position.y <= jump_from and position.y > jump_from - LEGS_ANIMATION){
			window->draw_img(DOODLE_RIGHT_JUMP, Rectangle(position.x , position.y , DOODLE_WIDTH , DOODLE_HEIGHT));
		}
		else{
			window->draw_img(DOODLE_IMAGE_RIGHT, Rectangle(position.x , position.y , DOODLE_WIDTH , DOODLE_HEIGHT));
		}
	}
}

void Doodle::jump_up(double move){
	if(status != HOLE){
		if(status == SPRING){
			move = move * 2;
			if(position.y == jump_from)
			count = 0;
			move = move - GRAVITY*3*count;
			count++;
			if(move < 1){
				move = 1;
			}
		}
		else{
			if(position.y == jump_from)
				count = 0;
			move = move - GRAVITY*count;
			count++;
			if(move < MIN_SPEED){
				move = MIN_SPEED;
			}
		}
		position = Point(position.x , position.y - (move));
		if(position.y == jump_from - jump_height){
			to_do = DOWN;
			count = 0;
		}
	}
}

void Doodle::jump_down(double move){
	if(status != HOLE){
		if(position.y == jump_from)
			count = 0;
		move = move + GRAVITY*0.5*count;
		count++;
		if(move < MAX_SPEED){
			move = MAX_SPEED;
			count = 0;
		}
		position = Point(position.x , position.y + (move));
		if(position.y == jump_from){
			to_do= UP;
		}
	}
}
std::string Doodle::get_todo(){
	return to_do;
}
std::string Doodle::get_face(){
	return face;
}
Point Doodle::get_position(){
	return position;
}
int Doodle::get_jump_from(){
	return jump_from;
}
int Doodle::get_jump_height(){
	return jump_height;
}
std::string Doodle::get_status(){
	return status;
}
bool Doodle::get_finish_game(){
	return finish_game;
}
void Doodle::set_jump_height(int jh){
	jump_height = jh;
}
void Doodle::set_jump_from(int h){
	jump_from = h;
}
void Doodle::set_todo(std::string up_down){
	to_do = up_down;
}
void Doodle::set_position(Point p){
	position = p;
}
void Doodle::set_status(std::string s){
	status = s;
}
void Doodle::set_count(int c){
	count = c;
}
