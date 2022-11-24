CC = g++
CXX = g++
CPPFLAGS = 

main: main.o game.o move.o pile.o player.o
	$(CXX) $(CFLAGS) -o main main.o game.o move.o pile.o player.o

main.o: main.cpp game.h

game.o: game.cpp game.h pile.h move.h player.h

move.o: move.cpp move.h pile.h

pile.o: pile.cpp pile.h

player.o: player.cpp player.h pile.h move.h
