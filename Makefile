CFLAGS= -Wall
player.o: player.cpp
	g++ -c player.cpp -g $(CFLAGS)

room.o: room.cpp
	g++ -c room.cpp -g $(CFLAGS)

game.o: game.cpp
	g++ -c game.cpp -g $(CFLAGS)

textAdventure: main.cpp game.cpp player.cpp room.cpp
	g++ -o textAdventure main.cpp game.cpp player.cpp room.cpp -g $(CFLAGS)

all: textAdventure

clean:
	rm -f *.o textAdventure
