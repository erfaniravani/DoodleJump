#ifndef _START_HPP
#define _START_HPP "_START_HPP"
#include <vector>
#include <string>
#include "RSDL/src/rsdl.hpp"
#include "defines.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include "inputfile.hpp"
#include "spring.hpp"
#include "hole.hpp"


class Start
{
public:
    void start_menu(Window* window);
    std::vector<Enemy*> prepare_game_enemy(std::vector<std::string> file_lines);
    std::vector<Platform*> prepare_game_platforms(std::vector<std::string> file_lines);
    std::vector<Spring*> prepare_game_springs(std::vector<std::string> file_lines);
    std::vector<Hole*> prepare_game_holes(std::vector<std::string> file_lines);
private:
	Point detect_position(std::vector<std::string> words);
};

#endif