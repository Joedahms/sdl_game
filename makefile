CFLAGS = -c -g

game: main.o game.o player.o npc.o character_factory.o character.o tile_factory.o water_tile.o dirt_tile.o tile.o camera.o main_menu.o
	g++ \
	main.o game.o player.o npc.o character_factory.o character.o tile_factory.o \
	water_tile.o dirt_tile.o tile.o camera.o main_menu.o \
       	-o game -lSDL2 -lSDL2_image

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

tile_factory.o: tile_factory.cpp tile_factory.h tile.h water_tile.h dirt_tile.h
	g++ $(CFLAGS) tile_factory.cpp

water_tile.o: water_tile.cpp water_tile.h tile.h
	g++ $(CFLAGS) water_tile.cpp

dirt_tile.o: dirt_tile.cpp dirt_tile.h tile.h
	g++ $(CFLAGS) dirt_tile.cpp

tile.o: tile.cpp tile.h
	g++ $(CFLAGS) tile.cpp

camera.o: camera/camera.cpp camera/camera.h
	g++ $(CFLAGS) camera/camera.cpp

main_menu.o: menu/main_menu.cpp menu/main_menu.h menu/menu.h
	g++ $(CFLAGS) menu/main_menu.cpp

clean: 
	rm game
	rm *.o
