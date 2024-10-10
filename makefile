CFLAGS = -c -g

game: main.o game.o player.o npc.o character_factory.o character.o tile_factory.o water_tile.o dirt_tile.o tile.o camera.o main_menu.o menu_background.o \
      tile_map.o
	g++ \
	main.o game.o player.o npc.o character_factory.o character.o tile_factory.o \
	water_tile.o dirt_tile.o tile.o camera.o main_menu.o menu_background.o \
	tile_map.o \
       	-o game -lSDL2 -lSDL2_image

main.o: main.cpp game.h
	g++ $(CFLAGS) main.cpp

game.o: game.cpp game.h tile_map.h
	g++ $(CFLAGS) game.cpp

player.o: player.cpp player.h character.h
	g++ $(CFLAGS) player.cpp

npc.o: npc.cpp npc.h character.h
	g++ $(CFLAGS) npc.cpp

character_factory.o: character_factory.cpp character_factory.h player.h npc.h
	g++ $(CFLAGS) character_factory.cpp

character.o: character.cpp character.h
	g++ $(CFLAGS) character.cpp

tile_factory.o: tile/tile_factory.cpp tile/tile_factory.h tile/tile.h tile/water_tile.h tile/dirt_tile.h
	g++ $(CFLAGS) tile/tile_factory.cpp

water_tile.o: tile/water_tile.cpp tile/water_tile.h tile/tile.h
	g++ $(CFLAGS) tile/water_tile.cpp

dirt_tile.o: tile/dirt_tile.cpp tile/dirt_tile.h tile/tile.h
	g++ $(CFLAGS) tile/dirt_tile.cpp

tile.o: tile/tile.cpp tile/tile.h
	g++ $(CFLAGS) tile/tile.cpp

camera.o: camera/camera.cpp camera/camera.h
	g++ $(CFLAGS) camera/camera.cpp

main_menu.o: menu/main_menu.cpp menu/main_menu.h menu/menu.h menu/menu_button.h
	g++ $(CFLAGS) menu/main_menu.cpp

menu_background.o: menu/menu_background.cpp menu/menu_background.h menu/menu_element.h
	g++ $(CFLAGS) menu/menu_background.cpp

tile_map.o: tile_map.cpp tile_map.h
	g++ $(CFLAGS) tile_map.cpp

clean: 
	rm game
	rm *.o
