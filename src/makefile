# Простейший Makefile для змейки
all:
	g++ main.cpp Food.cpp Snake.cpp -o main -std=c++11

run:
	g++ main.cpp Game.cpp Food.cpp Snake.cpp Record.cpp Menu.cpp Utils.cpp -o main -std=c++11
	./main

clean:
	del main.exe main 2>nul || rm -f main