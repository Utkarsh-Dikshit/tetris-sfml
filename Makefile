all: compile link

compile:
	g++ -I ./include -c src/*.cpp

link:
	g++ *.o -o tetris -L ./lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio