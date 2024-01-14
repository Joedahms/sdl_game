CFLAGS = -c -g

game: main.o game.o player.o npc.o character_factory.o character.o tile_factory.o one_tile.o two_tile.o tile.o
	g++ main.o game.o player.o npc.o character_factory.o character.o tile_factory.o one_tile.o two_tile.o tile.o -o game -lSDL2 -lSDL2_image

main.o: main.cpp game.h
	g++ $(CFLAGS) main.cpp

game.o: game.cpp game.h
	g++ $(CFLAGS) game.cpp

player.o: player.cpp player.h character.h
	g++ $(CFLAGS) player.cpp

npc.o: npc.cpp npc.h character.h
	g++ $(CFLAGS) npc.cpp

character_factory.o: character_factory.cpp character_factory.h player.h npc.h
	g++ $(CFLAGS) character_factory.cpp

character.o: character.cpp character.h
	g++ $(CFLAGS) character.cpp


tile_factory.o: tile_factory.cpp tile_factory.h tile.h one_tile.h two_tile.h
	g++ $(CFLAGS) tile_factory.cpp

one_tile.o: one_tile.cpp one_tile.h tile.h
	g++ $(CFLAGS) one_tile.cpp

two_tile.o: two_tile.cpp two_tile.h tile.h
	g++ $(CFLAGS) two_tile.cpp

tile.o: tile.cpp tile.h
	g++ $(CFLAGS) tile.cpp

clean: 
	rm game
	rm *.o
