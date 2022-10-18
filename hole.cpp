#include "hole.hpp"

Hole::Hole(int hole_x , int hole_y){
	position = Point(hole_x - (HOLE_WIDTH/2) , HEIGHT - hole_y - HOLE_HEIGHT);

}

void Hole::hole_draw(Window* window){
	window->draw_img(START_IMAGE, Rectangle(position.x , position.y , HOLE_WIDTH , HOLE_HEIGHT) , Rectangle(450, 105, HOLE_WIDTH, HOLE_HEIGHT));
}

Point Hole::get_position(){
	return position;
}

void Hole::set_position(Point pos){
	position = pos;
}