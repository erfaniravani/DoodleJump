#ifndef _INPUTFILE_HPP
#define _INPUTFILE_HPP "_INPUTFILE_HPP"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "defines.hpp"


std::vector<std::string> get_lines_of_file(std::vector<std::string> lines , std::string file_name);
std::vector<std::string> string_to_word(std::string str);

#endif