#include "start.hpp"

void Start::start_menu(Window* window)
{
    window->clear();
    window->fill_rect(Rectangle(0, 0, WIDTH, HEIGHT));
    window->draw_img(BEGIN_IMAGE , Rectangle(0, 0, WIDTH, HEIGHT) , Rectangle(0, 0, WIDTH, HEIGHT));
    window->show_text("click anywhere to start the game...", Point(10, HEIGHT-50), RED, FONT_FILE , 20);
    window->update_screen();
    while(true)
    {
        if(window->has_pending_event())
        {
            Event event = window->poll_for_event();
            if(event.get_type() == Event::EventType::LCLICK)
                break;
            else if(event.get_type() == Event::EventType::QUIT)
                throw std::runtime_error(QUIT);
        }
    }
    window->play_sound_effect("songs/win.wav");
    window->clear();
    window->update_screen();
}

Point Start::detect_position(std::vector<std::string> words){
	int x_position;
	int y_position;
	x_position = std::stoi(words[0]);
	if(std::stoi(words[1])%10==3){
		y_position = std::stoi(words[1]) - 1;
	}
	else{
		y_position  = std::stoi(words[1]);
	}
	return Point(x_position , y_position);
}

std::vector<Platform*> Start::prepare_game_platforms(std::vector<std::string> file_lines){
    std::vector<Platform*> platform_address;
    for(int i = 1 ; i < file_lines.size() ; i++){
        std::vector<std::string> words;
        words = string_to_word(file_lines[i]);
        Point platform_position = detect_position(words);
        if(words[2] == "platform"){        	
            Platform *platform_simple = new Platform(platform_position.x , platform_position.y);
            platform_address.push_back(platform_simple);
        }
        if(words[2] == "mplatform"){        	
            Mplatform *platform_moving = new Mplatform(platform_position.x , platform_position.y);
            platform_address.push_back(platform_moving);
        }
        if(words[2] == "bplatform"){
            Bplatform *platform_breakable = new Bplatform(platform_position.x , platform_position.y);
            platform_address.push_back(platform_breakable);
        }

    }
    return platform_address;
}

std::vector<Enemy*> Start::prepare_game_enemy(std::vector<std::string> file_lines){
    std::vector<Enemy*> enemy_address;
    for(int i = 1 ; i < file_lines.size() ; i++){
        std::vector<std::string> words;
        words = string_to_word(file_lines[i]);
        if(words[2] == "enemy"){
            Enemy *enemy_simple = new Enemy(std::stoi(words[0]) , std::stoi(words[1]));
            enemy_address.push_back(enemy_simple);
        }
    }
    return enemy_address;
}
std::vector<Spring*> Start::prepare_game_springs(std::vector<std::string> file_lines){
    std::vector<Spring*> sps;
    for(int i = 0 ; i < file_lines.size() ; i++){
        std::vector<std::string> words;
        words = string_to_word(file_lines[i]);
        if(words[2] == "spring"){
            Spring* sp_single = new Spring(std::stoi(words[0]) , std::stoi(words[1]));
            sps.push_back(sp_single);
        }
    }
    return sps;
}

std::vector<Hole*> Start::prepare_game_holes(std::vector<std::string> file_lines){
    std::vector<Hole*> holes;
    for(int i = 0 ; i < file_lines.size() ; i++){
        std::vector<std::string> words;
        words = string_to_word(file_lines[i]);
        if(words[2] == "hole"){
            Hole* hole_single = new Hole(std::stoi(words[0]) , std::stoi(words[1]));
            holes.push_back(hole_single);
        }
    }
    return holes;
}



