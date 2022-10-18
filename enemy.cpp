#include "enemy.hpp"

Enemy::Enemy(int enemy_x , int enemy_y){
	position = Point(enemy_x - (ENEMY_WIDTH/2) , HEIGHT - enemy_y - ENEMY_HEIGHT);
}

void Enemy::enemy_draw(Window* window){
	window->draw_img(START_IMAGE, Rectangle(position.x , position.y , ENEMY_WIDTH , ENEMY_HEIGHT) , Rectangle(125, 0, 170, 185));
}

Point Enemy::get_position(){
	return position;
}
void Enemy::set_position(Point p){
	position = p;
}