CFLAGS = -c -g
SRC = src/

game: main.o game.o player.o npc.o character_factory.o character.o tile_factory.o water_tile.o dirt_tile.o tile.o camera.o main_menu.o menu_background.o \
      tile_map.o
	g++ \
	main.o game.o player.o npc.o character_factory.o character.o tile_factory.o \
	water_tile.o dirt_tile.o tile.o camera.o main_menu.o menu_background.o \
	tile_map.o \
       	-o game -lSDL2 -lSDL2_image

main.o: $(SRC)main.cpp $(SRC)game.h
	g++ $(CFLAGS) $(SRC)main.cpp

game.o: $(SRC)game.cpp $(SRC)game.h $(SRC)tile_map.h
	g++ $(CFLAGS) $(SRC)game.cpp

player.o: $(SRC)player.cpp $(SRC)player.h $(SRC)character.h
	g++ $(CFLAGS) $(SRC)player.cpp

npc.o: $(SRC)npc.cpp $(SRC)npc.h $(SRC)character.h
	g++ $(CFLAGS) $(SRC)npc.cpp

character_factory.o: $(SRC)character_factory.cpp $(SRC)character_factory.h $(SRC)player.h $(SRC)npc.h
	g++ $(CFLAGS) $(SRC)character_factory.cpp

character.o: $(SRC)character.cpp $(SRC)character.h
	g++ $(CFLAGS) $(SRC)character.cpp

tile_factory.o: $(SRC)tile/tile_factory.cpp $(SRC)tile/tile_factory.h $(SRC)tile/tile.h $(SRC)tile/water_tile.h $(SRC)tile/dirt_tile.h
	g++ $(CFLAGS) $(SRC)tile/tile_factory.cpp

water_tile.o: $(SRC)tile/water_tile.cpp $(SRC)tile/water_tile.h $(SRC)tile/tile.h
	g++ $(CFLAGS) $(SRC)tile/water_tile.cpp

dirt_tile.o: $(SRC)tile/dirt_tile.cpp $(SRC)tile/dirt_tile.h $(SRC)tile/tile.h
	g++ $(CFLAGS) $(SRC)tile/dirt_tile.cpp

tile.o: $(SRC)tile/tile.cpp $(SRC)tile/tile.h
	g++ $(CFLAGS) $(SRC)tile/tile.cpp

camera.o: $(SRC)camera/camera.cpp $(SRC)camera/camera.h
	g++ $(CFLAGS) $(SRC)camera/camera.cpp

main_menu.o: $(SRC)menu/main_menu.cpp $(SRC)menu/main_menu.h $(SRC)menu/menu.h $(SRC)menu/menu_button.h
	g++ $(CFLAGS) $(SRC)menu/main_menu.cpp

menu_background.o: $(SRC)menu/menu_background.cpp $(SRC)menu/menu_background.h $(SRC)menu/menu_element.h
	g++ $(CFLAGS) $(SRC)menu/menu_background.cpp

tile_map.o: $(SRC)tile_map.cpp $(SRC)tile_map.h
	g++ $(CFLAGS) $(SRC)tile_map.cpp

clean: 
	rm game
	rm *.o
