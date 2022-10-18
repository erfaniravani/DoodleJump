#include "handler.hpp"

Handler::Handler(){
	int rst_game = 1;
	Window *window = new Window(WIDTH , HEIGHT , WINDOW_NAME);
	while(rst_game == 1){
		rst_game--;
		std::vector<std::string> file_lines;
		std::vector<Platform*> platforms;
		std::vector<Enemy*> enemies;
		file_lines = get_lines_of_file(file_lines , "ca5.txt");
		Doodle *_doodle = new Doodle(400 , 0);
		Start start;
		start.start_menu(window);
		platforms = start.prepare_game_platforms(file_lines);
		enemies = start.prepare_game_enemy(file_lines);
		std::vector<Spring*> springs = start.prepare_game_springs(file_lines);
		std::vector<Hole*> holes = start.prepare_game_holes(file_lines);
		Game game(window , _doodle);
		int go_right = 0;
		int go_left = 0; 
		bool in_game = true;
		while(in_game){
			game.update_func(window , platforms , enemies , go_right , go_left , springs , holes);
			game.draw_func(window , platforms , enemies , springs , holes);
			delay(35);
			if(game.restart_game == 1){
				rst_game++;
				in_game = false;
				std::cout << rst_game << std::endl;
			}
		}
	}
}

