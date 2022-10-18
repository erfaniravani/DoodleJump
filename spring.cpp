#include "spring.hpp"

Spring::Spring(int spring_x , int spring_y){
	position = Point(spring_x - (SPRING_WIDTH/2) , HEIGHT - spring_y - SPRING_HEIGHT);
	on_spring = false;
	frame_count = 0;
}
void Spring::spring_draw(Window* window){
	if(!on_spring)
		window->draw_img(START_IMAGE, Rectangle(position.x , position.y , SPRING_WIDTH , SPRING_HEIGHT) , Rectangle(810, 220, 42, 70));
	else if(on_spring){
		window->draw_img(START_IMAGE, Rectangle(position.x , position.y , 42 , 35) , Rectangle(809, 180, 42, 35));
		frame_count++;
		if(frame_count == SPRING_ANIMATION){
			frame_count = 0;
			on_spring = false;
		}
	}
}
Point Spring::get_position(){
	return position;
}
void Spring::set_position(Point p){
	position = p;
}
void Spring::set_on_spring(bool on){
	if(on)
		on_spring = true;
	else
		on_spring = false;
}