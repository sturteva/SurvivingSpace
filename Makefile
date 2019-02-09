CFLAGS= -Wall -g -std=c++11 

survivingSpace: main.cpp game.o player.o room.o dataio.o inventory.o parser.o
	g++ -o survivingSpace main.cpp game.o player.o room.o dataio.o inventory.o parser.o $(CFLAGS)

game.o: game.cpp player.hpp parser.hpp room.hpp
	g++ -c game.cpp player.hpp parser.hpp room.hpp $(CFLAGS)

player.o: player.cpp room.hpp
	g++ -c player.cpp room.hpp $(CFLAGS)

room.o: room.cpp
	g++ -c room.cpp $(CFLAGS)

dataio.o: dataio.cpp room.hpp game.hpp
	g++ -c dataio.cpp room.hpp game.hpp $(CFLAGS)

inventory.o: inventory.cpp player.hpp
	g++ -c inventory.cpp player.hpp $(CFLAGS)

parser.o: parser.cpp
	g++ -c parser.cpp $(CFLAGS)

all: game.o player.o room.o dataio.o inventory.o parser.o survivingSpace

clean:
	rm -f *.o survivingSpace
