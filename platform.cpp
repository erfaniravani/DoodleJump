#include "platform.hpp"

Platform::Platform(int platform_x , int platform_y){
	position = Point(platform_x - (PLATFORM_WIDTH/2) , HEIGHT - platform_y - PLATFORM_HEIGHT);
	breakable = false;
	broken = false;
	animate = 0;

}
Point Platform::get_position(){
	return position;
}
bool Platform::get_breakable(){
	return breakable;
}
void Platform::set_broken(bool b){
	broken = b;
}
void Platform::set_position(Point p){
	position = p;
}
void Platform::platform_draw(Window* window){
	window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , PLATFORM_HEIGHT) , Rectangle(0, 0, 120, 36));
}

void Platform::update_position(){
	position = Point(position.x , position.y);
}
bool Platform::get_broken(){
	return broken;
}

Mplatform::Mplatform(int mplatform_x , int mplatform_y):
					Platform(mplatform_x , mplatform_y)
{
	next_position = Point(mplatform_x , mplatform_y);
	reverse = 0;
}
Point Mplatform::get_position(){
	return position;
}
bool Mplatform::get_breakable(){
	return breakable;
}
void Mplatform::set_broken(bool b){
	broken = b;
}
void Mplatform::set_position(Point p){
	position = p;
}

void Mplatform::update_position(){
	if(reverse == 0){
		next_position = Point(position.x - STEP_MOVES_PLATFORM , position.y);
	}
	else if(reverse == 1){
		next_position = Point(position.x + STEP_MOVES_PLATFORM , position.y);	
	}
	if(next_position.x < 0){
		reverse = 1;
	}
	if(next_position.x > WIDTH - DOODLE_HEIGHT){
		reverse = 0;
	}
	position = next_position;
}

void Mplatform::platform_draw(Window* window){
	window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , PLATFORM_HEIGHT) , Rectangle(0, 37, 120, 36));
}

bool Mplatform::get_broken(){
	return broken;
}

Bplatform::Bplatform(int bplatform_x , int bplatform_y):
					Platform(bplatform_x , bplatform_y)
{
	breakable = true;
}
Point Bplatform::get_position(){
	return position;
}
bool Bplatform::get_breakable(){
	return breakable;
}
void Bplatform::set_broken(bool b){
	broken = b;
}
void Bplatform::set_position(Point p){
	position = p;
}
void Bplatform::update_position(){
	
	position = Point(position.x , position.y);
	
}

bool Bplatform::get_broken(){
	return broken;
}

void Bplatform::platform_draw(Window* window){
	if(broken == false)
		window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , PLATFORM_HEIGHT) , Rectangle(2, 145, 120, 36));
	if(broken == true){
		if(animate < 10){
			window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , PLATFORM_HEIGHT) , Rectangle(2, 183, 120, 38));
			animate++;
			broken = true;
		}
		if(animate > 9 && animate < 15){
			window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , PLATFORM_HEIGHT) , Rectangle(2, 225, 120, 58));
			animate++;
		}
		if(animate > 14 && animate < 20){
			window->draw_img(START_IMAGE, Rectangle(position.x , position.y , PLATFORM_WIDTH , 90) , Rectangle(2, 286, 120, 82));
			animate++;
		}
		else{
			window->draw_img(START_IMAGE, Rectangle(position.x , position.y-15+animate , PLATFORM_WIDTH , 90) , Rectangle(2, 286, 120, 82));
			animate = animate + 5;
		}

	}
	
}