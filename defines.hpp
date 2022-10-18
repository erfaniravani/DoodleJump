#ifndef _DEFINES_HPP
#define _DEFINES_HPP "_DEFINES_HPP"

#include <string>
const int WIDTH = 480;
const int HEIGHT = 768;
const int PLATFORM_WIDTH = 90;
const int PLATFORM_HEIGHT = 27;
const int ENEMY_WIDTH = 102;
const int ENEMY_HEIGHT = 138;
const int DOODLE_WIDTH = 93;
const int DOODLE_HEIGHT = 90;
const int SPRING_HEIGHT = 42;
const int SPRING_WIDTH = 35;
const int HOLE_HEIGHT = 130;
const int HOLE_WIDTH = 140;
const int STEP_MOVES_PLATFORM = 4;
const double STEP_MOVES_DOODLE = 10;
const int MOVE_DOODLE = 10;
const int JUMP_UP = 200;
const int INSENSIVITY_SIDE_1 = 20;
const int INSENSIVITY_SIDE_2 = 30;
const int LEGS_ANIMATION = 35;
const int HOLE_ANIMATION = 50;
const int SPRING_ANIMATION = 10;
const double GRAVITY = 0.2;
const int MAX_SPEED = 15;
const int MIN_SPEED = 1;
const std::string QUIT = "quit";
const std::string FALLING = "falling";
const std::string HOLE = "on hole";
const std::string SPRING = "on spring";
const std::string PLATFORM = "on platform";
const std::string FALLING_MASSAGE = "you felt down";
const std::string ENEMY = "enemy";
const std::string ENEMY_MASSAGE = "enemy ate you";
const std::string HOLE_MASSAGE = "you are in hole";
const std::string UP = "up";
const std::string DOWN = "down";
const std::string LEFT = "left";
const std::string RIGHT = "right";
const std::string REST = "rest";
const std::string JUMP = "jump";
const std::string WINDOW_NAME = "doodle jump";
const std::string START_IMAGE = "assets/main_pictures/game-tiles.png";
const std::string BEGIN_IMAGE = "assets/Doodle-Jump-head.jpeg";
const std::string END_IMAGE = "assets/over.jpeg";
const std::string BACKGROUND_IMAGE = "assets/main_pictures/background.png";
const std::string DOODLE_IMAGE_LEFT = "assets/main_pictures/left.png";
const std::string DOODLE_LEFT_JUMP = "assets/main_pictures/left_jumping.png";
const std::string DOODLE_IMAGE_RIGHT = "assets/main_pictures/right.png";
const std::string DOODLE_RIGHT_JUMP = "assets/main_pictures/right_jumping.png";
const std::string FONT_FILE = "Fonts/freesans-font/FreeSans-1Zge.otf";
const std::string FONT_FILE_2 = "Fonts/freesans-font/FreeSansBoldOblique-BYJ3.otf";
const std::string BREAK_PLATFORM_SONG = "songs/breaking-arcade.wav";
const std::string JUMP_SONG = "songs/jump.wav";
const std::string SPRING_SONG = "songs/jump-spring.wav";
const std::string HOLE_SONG = "songs/falling-sound-arcade.wav";
const std::string ENEMY_SONG = "songs/monster-crash.wav";



#endif