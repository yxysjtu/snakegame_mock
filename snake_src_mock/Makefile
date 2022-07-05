snakegame: main.o game.o snake.o food.o
	g++ -o snakegame main.o game.o snake.o food.o -l curses
main.o: main.cpp game.h
	g++ -c main.cpp
game.o: game.cpp snake.h food.h
	g++ -c game.cpp
snake.o: snake.cpp
	g++ -c snake.cpp
food.o: food.cpp
	g++ -c food.cpp
clean:
	rm *.o 
	rm snakegame
	rm record.dat
