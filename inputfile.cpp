#include "inputfile.hpp"


std::vector<std::string> get_lines_of_file(std::vector<std::string> lines , std::string file_name){

    std::ifstream in(file_name);

    if(!in) {
        std::cout << "Cannot open input file.\n";
        return lines;
    }

    char str[255];

    while(in) {
        in.getline(str, 255); 
        if(in) 
          lines.push_back(str);
    }

    in.close();
    return lines;
}
std::vector<std::string> string_to_word(std::string str){
	std::vector<std::string> words; 
    std::string word = ""; 
    for (auto x : str)  { 
    	if (x == ' ' || x == '(' || x == ')' || x == ',' || x == ';' || x == '\n'){ 
            if(word != "")  
                words.push_back(word);
            word = ""; 
        } 
        else{ 
            word = word + x; 
        } 
    }    
    words.push_back(word);
    return words;
}




 