CXX = g++
CXXFLAGS = -g -Wall -Isrc
LDLIBS = -lSDL2 -lSDL2_image
BUILD_DIR = build
GAME_DIR = game

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

$(shell mkdir -p $(BUILD_DIR) $(GAME_DIR))

$(GAME_DIR)/game: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(GAME_DIR)/game

.PHONY: run

run:
	@cd $(GAME_DIR) && ./game
