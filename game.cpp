#include "game.hpp"

Game::Game(Window* _window , Doodle* _doodle){
	window = _window;
	score = 0;
    doodle = _doodle;
    game_over = false;
    restart_game = 0;
}

void Game::update_doodle_right(){
    doodle->go_right(MOVE_DOODLE);
}
void Game::update_doodle_left(){
    doodle->go_left(MOVE_DOODLE);
}


void Game::update_score( int diff){
	if(HEIGHT - doodle->get_position().y - DOODLE_HEIGHT > score)
        score = HEIGHT - doodle->get_position().y - DOODLE_HEIGHT;
    if(diff > 0)
        score += diff;

}

void Game::doodle_up(){
	doodle->jump_up(STEP_MOVES_DOODLE);
    if(doodle->get_position().y < doodle->get_jump_from() - doodle->get_jump_height()){
        doodle->set_todo(DOWN);
        doodle->set_count(0);
        doodle->set_status(REST);
    }
}
void Game::doodle_down(){
	doodle->jump_down(STEP_MOVES_DOODLE);
    if(doodle->get_position().y > doodle->get_jump_from()){
        doodle->set_todo(DOWN);
        doodle->set_count(0);
    }
}

void Game::update_doodle_on_platform(std::vector<Platform*> platforms , Window* window){
	for(int i = 0 ; i < platforms.size() ; i++){
		int should_update = 1;
        if(doodle_on_platform(doodle , platforms[i])){
        	doodle->set_status(PLATFORM);
        	if(platforms[i]->get_breakable()){
                if(!platforms[i]->get_broken())
                    window->play_sound_effect(BREAK_PLATFORM_SONG);
                platforms[i]->set_broken(true);
            	should_update = 0;
            }
            if(should_update){
                window->play_sound_effect(JUMP_SONG);
            	doodle->set_jump_from(platforms[i]->get_position().y - DOODLE_HEIGHT);
            	doodle->set_todo(UP);

            }
        }

    }
}

void Game::update_doodle_on_spring(std::vector<Spring*> sp){
    for(int i = 0 ; i < sp.size() ; i++){
        if(doodle_spring(doodle , sp[i])){
            window->play_sound_effect(SPRING_SONG);
            sp[i]->set_on_spring(true);
            doodle->set_jump_from(sp[i]->get_position().y - DOODLE_HEIGHT);
            doodle->set_todo(UP);
            doodle->set_jump_height(2*JUMP_UP);
            doodle->set_status(SPRING);
            break;
        }
        else{
            doodle->set_jump_height(JUMP_UP);
        }
    }
}

int Game::update_camera(std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes){
    int height_diff;
	if(doodle->get_position().y + DOODLE_HEIGHT < (HEIGHT/2)){
		doodle->set_count(0);
		height_diff = (HEIGHT/2) - doodle->get_position().y - DOODLE_HEIGHT;
	    update_camera_doodle(height_diff);
        update_camera_platform(platforms , height_diff);
        update_camera_enemy(enemies , height_diff);
        update_camera_spring(sp , height_diff);
        update_camera_hole(holes , height_diff);
	}
    else 
        height_diff = 0;
    return height_diff;
}

void Game::update_camera_hole(std::vector<Hole*> holes , int height_diff){
    for(int i = 0 ; i < holes.size() ; i++){
        int hole_x = holes[i]->get_position().x;
        int hole_y = holes[i]->get_position().y + height_diff;
        holes[i]->set_position(Point(hole_x , hole_y));
    }
}

void Game::update_camera_doodle(int height_diff){
    int j_from = doodle->get_jump_from();
    int doodle_x = doodle->get_position().x;
    int doodle_y = doodle->get_position().y + height_diff;
    doodle->set_jump_from(j_from + height_diff);
    doodle->set_position(Point(doodle_x , doodle_y));
}

void Game::update_camera_spring(std::vector<Spring*> sp , int height_diff){
    for(int i = 0 ; i < sp.size() ; i++){
        int spring_x = sp[i]->get_position().x;
        int spring_y = sp[i]->get_position().y + height_diff;
        sp[i]->set_position(Point(spring_x , spring_y));
    }
}

void Game::update_camera_enemy(std::vector<Enemy*> enemies , int height_diff){
    for(int i = 0 ; i < enemies.size() ; i++){
        int enemy_x = enemies[i]->get_position().x;
        int enemy_y = enemies[i]->get_position().y + height_diff;
        enemies[i]->set_position(Point(enemy_x , enemy_y));
    }
}

void Game::update_camera_platform(std::vector<Platform*> platforms , int height_diff){
    for(int i = 0 ; i < platforms.size() ; i++){
        int platform_x = platforms[i]->get_position().x;
        int platform_y = platforms[i]->get_position().y + height_diff;
        platforms[i]->set_position(Point(platform_x , platform_y));
    }
}

void Game::update_game(std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes , Window* window){
    int diff;
    diff = update_camera(platforms , enemies , sp , holes);
    update_score(diff);
    if(doodle->get_todo() == UP){
    	doodle_up();
    }
    else if(doodle->get_todo() == DOWN){
        doodle_down();
        update_doodle_on_platform(platforms , window);
        update_doodle_on_spring(sp);
    }
    if(doodle_fall()){
    	game_over_reason = FALLING;
    	game_over = true;
    }
    check_enemy(enemies , window);
    check_holes(holes);
   
}

void Game::check_holes(std::vector<Hole*> holes){
    for(int i = 0 ; i < holes.size() ; i++){
        if(doodle_on_hole(doodle , holes[i])){
            window->play_sound_effect(HOLE_SONG);
            doodle->set_status(HOLE);
            if(doodle->get_finish_game()){
                game_over = true;
                game_over_reason = HOLE;
            }
        }
    }
}

bool Game::doodle_on_hole(Doodle* doodle , Hole* hole){
    int doodle_y_begin = doodle->get_position().y;
    int doodle_x_begin = doodle->get_position().x;
    int hole_y_begin = hole->get_position().y;
    int hole_x_begin = hole->get_position().x;
    int is_on = 0;
    if(same_height_hole(hole_y_begin , doodle_y_begin)){
        if(doodle->get_face() == RIGHT){
            if(same_width_right_hole(hole_x_begin , doodle_x_begin)){
                is_on = 1;
            }
        }
        if(doodle->get_face() == LEFT){
            if(same_width_left_hole(hole_x_begin , doodle_x_begin)){
                is_on = 1;
            }
        }
    }
    if(is_on == 1)
        return true;
    else
        return false;

}

bool Game::same_height_hole(int hole_h_begin , int doodle_h_begin){
    int hole_h_end = hole_h_begin + HOLE_HEIGHT;
    int doodle_h_end = doodle_h_begin + DOODLE_HEIGHT;
    if(hole_h_begin+(INSENSIVITY_SIDE_1*5) < doodle_h_end and doodle_h_begin < hole_h_end-(INSENSIVITY_SIDE_1*5))
        return true;
    else
        return false;
}

bool Game::same_width_right_hole(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + HOLE_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - (INSENSIVITY_SIDE_1*3)) and (doodle_x < entity_x_end - (INSENSIVITY_SIDE_2*3))))
        return true;
    else
        return false;
}
bool Game::same_width_left_hole(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + HOLE_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - (INSENSIVITY_SIDE_2*3)) and (doodle_x < entity_x_end - (INSENSIVITY_SIDE_1*3))))
        return true;
    else
        return false;
}

void Game::check_enemy(std::vector<Enemy*> enemies , Window* window){
	for(int i = 0 ; i < enemies.size() ; i++){
        if(doodle_on_enemy(doodle , enemies[i])){
            window->play_sound_effect(ENEMY_SONG);
            game_over = true;
            game_over_reason = ENEMY;
        }
    }
}

bool Game::doodle_fall(){
	if(HEIGHT - DOODLE_HEIGHT < doodle->get_position().y)
		return true;
	else
		return false;
}

void Game::draw_game_over(){
    window->clear();
    window->draw_img(END_IMAGE , Rectangle(0, 0, WIDTH, HEIGHT-100));
    if(game_over_reason == FALLING){
        window->show_text(FALLING_MASSAGE, Point(150, HEIGHT-300), RED, FONT_FILE , 30);    
    }
    if(game_over_reason == ENEMY){
        window->show_text(ENEMY_MASSAGE, Point(150, HEIGHT-300), RED, FONT_FILE , 30);
    }
    if(game_over_reason == HOLE){
        window->show_text(HOLE_MASSAGE, Point(150, HEIGHT-300), RED, FONT_FILE , 30);
    }
    window->show_text("press 'r' to restart the game", Point(120, HEIGHT-200), GREEN, FONT_FILE , 20);
    window->show_text("your score", Point(50, HEIGHT-100), GREEN, FONT_FILE , 50);
    window->show_text(std::to_string(score), Point(350, HEIGHT-100), GREEN, FONT_FILE , 50);
    window->update_screen();
    while(true)
    {
        if(window->has_pending_event())
        {
            Event event = window->poll_for_event();
            if(event.get_type() == Event::EventType::LCLICK)
                throw std::runtime_error(QUIT);
            else if(event.get_type() == Event::EventType::QUIT)
                throw std::runtime_error(QUIT);
            else if(event.get_type() == Event::EventType::KEY_PRESS){
                if(event.get_pressed_key() == 'r'){
                    restart_game = 1;
                    break;
                }
                else if(event.get_pressed_key() == '\e')
                    throw std::runtime_error(QUIT);
            }
        }
    }
}

void Game::draw_game(){
	if(game_over == false){
	    doodle->doodle_draw(window);
	    window->show_text("score: ", Point(10, 0), RED, FONT_FILE , 20);
	    window->show_text(std::to_string(score), Point(100, 0), RED, FONT_FILE , 20);
	}
	if(game_over == true){
        draw_game_over();
	}
}

void Game::draw_func(Window* window , std::vector<Platform*> platforms , std::vector<Enemy*> enemies , std::vector<Spring*> sp , std::vector<Hole*> holes){
    window->clear();
    window->draw_img(BACKGROUND_IMAGE);
    for(int i = 0 ; i < holes.size() ; i++){
        holes[i]->hole_draw(window);
    }
    for(int i = 0 ; i < platforms.size() ; i++){
        platforms[i]->platform_draw(window);
    }

    for(int i = 0 ; i < enemies.size() ; i++){
        enemies[i]->enemy_draw(window);
    }


    for(int i = 0 ; i < sp.size() ; i++){
        sp[i]->spring_draw(window);
    }
    
    draw_game();

    window->update_screen();

}

void Game::update_func(Window* window , std::vector<Platform*> platforms , std::vector<Enemy*> enemies , int& go_right , int& go_left ,
                       std::vector<Spring*> sp , std::vector<Hole*> holes){
    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        if(event.get_type() == Event::EventType::QUIT){
            throw std::runtime_error(QUIT);
        }
        else if(event.get_type() == Event::EventType::KEY_PRESS){
            if(event.get_pressed_key() == '\e')
                throw std::runtime_error(QUIT);
            else if(event.get_pressed_key() == 'a'){
                go_left = 1;
            }
            else if(event.get_pressed_key() == 'd'){
                go_right = 1;
            }
        }
        else if(event.get_type() == Event::EventType::KEY_RELEASE){
            go_right = 0;
            go_left = 0;
        }
    }
    if(doodle->get_status() != HOLE){
        if(go_right == 1){
            update_doodle_right();
        }
        if(go_left == 1){
            update_doodle_left();
        }
    }
    
    update_game(platforms , enemies , sp , holes , window);
    for(int i = 0 ; i < platforms.size() ; i++){
        platforms[i]->update_position();
    }
}

bool Game::doodle_on_platform(Doodle* doodle  , Platform* platform){
    int doodle_y = doodle->get_position().y + DOODLE_HEIGHT;
    int doodle_x = doodle->get_position().x;
    int platform_y = platform->get_position().y;
    int platform_x_begin = platform->get_position().x;
    int on_platform = 0;
    if(same_height_platform(platform_y , doodle_y)){
        if(doodle->get_face() == RIGHT){
            if(same_width_right_platform(platform_x_begin , doodle_x)){
                on_platform = 1;
            }
        }
        if(doodle->get_face() == LEFT){
            if(same_width_left_platform(platform_x_begin , doodle_x)){
                on_platform = 1;
            }
        }
    }
    if(on_platform == 1)
        return true;
    else
        return false;
}

bool Game::doodle_spring(Doodle* doodle , Spring* sp){
    int doodle_y = doodle->get_position().y + DOODLE_HEIGHT;
    int doodle_x = doodle->get_position().x;
    int spring_y = sp->get_position().y;
    int spring_x_begin = sp->get_position().x;
    int on_spring = 0;
    if(same_height_spring(spring_y , doodle_y)){
        if(doodle->get_face() == RIGHT){
            if(same_width_right_spring(spring_x_begin , doodle_x))
                on_spring = 1;
        }
        if(doodle->get_face() == LEFT){
            if(same_width_left_spring(spring_x_begin , doodle_x))
                on_spring = 1;
        }
    }
    if(on_spring == 1)
        return true;
    else
        return false;
}

bool Game::doodle_on_enemy(Doodle* doodle , Enemy* enemy){
    int doodle_y_begin = doodle->get_position().y;
    int doodle_x_begin = doodle->get_position().x;
    int enemy_y_begin = enemy->get_position().y;
    int enemy_x_begin = enemy->get_position().x;
    int is_on = 0;
    if(same_height_enemy(enemy_y_begin , doodle_y_begin)){
        if(doodle->get_face() == RIGHT){
            if(same_width_right_enemy(enemy_x_begin , doodle_x_begin)){
                is_on = 1;
            }
        }
        if(doodle->get_face() == LEFT){
            if(same_width_left_enemy(enemy_x_begin , doodle_x_begin)){
                is_on = 1;
            }
        }
    }
    if(is_on == 1)
        return true;
    else
        return false;

}

bool Game::same_width_right_enemy(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + ENEMY_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - (INSENSIVITY_SIDE_1*2)) and (doodle_x < entity_x_end - (INSENSIVITY_SIDE_2*2))))
        return true;
    else
        return false;
}
bool Game::same_width_left_enemy(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + ENEMY_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - (INSENSIVITY_SIDE_2*2)) and (doodle_x < entity_x_end - (INSENSIVITY_SIDE_1*2))))
        return true;
    else
        return false;
}

bool Game::same_width_right_spring(int entity_x_begin , int doodle_x){
    int spring_x_end = entity_x_begin + SPRING_WIDTH;
    if((entity_x_begin < doodle_x + DOODLE_WIDTH - INSENSIVITY_SIDE_1) and (doodle_x < spring_x_end - INSENSIVITY_SIDE_2))
        return true;
    else
        return false;
}

bool Game::same_width_left_spring(int entity_x_begin , int doodle_x){
    int spring_x_end = entity_x_begin + SPRING_WIDTH;
    if((entity_x_begin < doodle_x + DOODLE_WIDTH - INSENSIVITY_SIDE_2) and (doodle_x < spring_x_end - INSENSIVITY_SIDE_1))
        return true;
    else
        return false;
}

bool Game::same_width_right_platform(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + PLATFORM_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - INSENSIVITY_SIDE_1) and (doodle_x < entity_x_end - INSENSIVITY_SIDE_2)))
        return true;
    else
        return false;
}
bool Game::same_width_left_platform(int entity_x_begin , int doodle_x){
    int entity_x_end = entity_x_begin + PLATFORM_WIDTH;
    if(((entity_x_begin < doodle_x + DOODLE_WIDTH - INSENSIVITY_SIDE_2) and (doodle_x < entity_x_end - INSENSIVITY_SIDE_1)))
        return true;
    else
        return false;
}
bool Game::same_height_spring(int spring_y_begin , int doodle_h){
    int spring_y_end = spring_y_begin + SPRING_HEIGHT;
    if(spring_y_begin < doodle_h and doodle_h < spring_y_end)
        return true;
    else
        return false;
}

bool Game::same_height_platform(int platform_h_begin , int doodle_h){
    int platform_h_end = platform_h_begin + PLATFORM_HEIGHT;
    if(platform_h_begin < doodle_h and doodle_h < platform_h_end)
        return true;
    else
        return false;
}
bool Game::same_height_enemy(int enemy_h_begin , int doodle_h_begin){
    int enemy_h_end = enemy_h_begin + ENEMY_HEIGHT;
    int doodle_h_end = doodle_h_begin + DOODLE_HEIGHT;
    if(enemy_h_begin+(INSENSIVITY_SIDE_1*2) < doodle_h_end and doodle_h_begin < enemy_h_end-(INSENSIVITY_SIDE_1*2))
        return true;
    else
        return false;
}
