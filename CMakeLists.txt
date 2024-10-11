cmake_minimum_required(VERSION 3.7)
project(sdlGameEngine VERSION 0.01 DESCRIPTION "Game engine in SDL" LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(sdlGameEngine
src/camera/camera.cpp
src/camera/camera.h
src/character.cpp
src/character_factory.cpp
src/character_factory.h
src/character.h
src/game.cpp
src/game.h
src/logger.cpp
src/logger.h
src/main.cpp
src/menu/main_menu.cpp
src/menu/main_menu.h
src/menu/menu_background.cpp
src/menu/menu_background.h
src/menu/menu_button.h
src/menu/menu_element.h
src/menu/menu.h
src/npc.cpp
src/npc.h
src/player.cpp
src/player.h
src/tile/dirt_tile.cpp
src/tile/dirt_tile.h
src/tile/tile.cpp
src/tile/tile_factory.cpp
src/tile/tile_factory.h
src/tile/tile.h
src/tile/water_tile.cpp
src/tile/water_tile.h
src/tile_map.cpp
src/tile_map.h)
add_executable(tests 
test/main_test.cpp
test/game_test.cpp)

target_compile_features(sdlGameEngine PRIVATE cxx_std_20)

target_link_libraries(sdlGameEngine ${SDL2_LIBRARIES} SDL2_image)
target_link_libraries(tests PRIVATE Catch2::Catch2)

