CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
doodleJump.out: main.o rsdl.o start.o platform.o inputfile.o enemy.o game.o doodle.o spring.o hole.o handler.o
	$(CC) main.o rsdl.o start.o platform.o inputfile.o enemy.o game.o doodle.o spring.o hole.o handler.o $(CCFLAGS) -o doodleJump.out
main.o: RSDL/src/rsdl.hpp main.cpp start.hpp handler.hpp
	$(CC) -c main.cpp -o main.o

handler.o: RSDL/src/rsdl.hpp handler.cpp handler.hpp  defines.hpp inputfile.hpp game.hpp enemy.hpp doodle.hpp platform.hpp spring.hpp hole.hpp
	$(CC) -c handler.cpp -o handler.o

start.o: RSDL/src/rsdl.hpp start.hpp start.cpp platform.hpp defines.hpp inputfile.hpp enemy.hpp spring.hpp hole.hpp
	$(CC) -c start.cpp -o start.o

game.o: RSDL/src/rsdl.hpp game.hpp game.cpp doodle.hpp defines.hpp inputfile.hpp enemy.hpp platform.hpp spring.hpp hole.hpp
	$(CC) -c game.cpp -o game.o

doodle.o: RSDL/src/rsdl.hpp doodle.hpp doodle.cpp defines.hpp 
	$(CC) -c doodle.cpp -o doodle.o

platform.o: RSDL/src/rsdl.hpp platform.hpp platform.cpp defines.hpp 
	$(CC) -c platform.cpp -o platform.o

enemy.o: RSDL/src/rsdl.hpp enemy.hpp enemy.cpp defines.hpp 
	$(CC) -c enemy.cpp -o enemy.o

spring.o: RSDL/src/rsdl.hpp spring.hpp spring.cpp defines.hpp
	$(CC) -c spring.cpp -o spring.o

hole.o: RSDL/src/rsdl.hpp hole.hpp hole.cpp defines.hpp
	$(CC) -c hole.cpp -o hole.o

inputfile.o: RSDL/src/rsdl.hpp defines.hpp inputfile.hpp inputfile.cpp
	$(CC) -c inputfile.cpp -o inputfile.o

rsdl.o: RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c RSDL/src/rsdl.cpp -o rsdl.o
.PHONY: clean
clean:
	rm -r *.o