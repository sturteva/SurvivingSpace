CFLAGS= -Wall -g 

survivingSpace: main.cpp game.cpp player.cpp room.cpp dataio.cpp inventory.cpp
	g++ -o survivingSpace main.cpp game.cpp dataio.cpp player.cpp room.cpp inventory.cpp $(CFLAGS)

all: survivingSpace

clean:
	rm -f *.o survivingSpace
