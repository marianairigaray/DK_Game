# Define the compiler
CC = gcc

# Define raylib path
RAYLIB_PATH = ./libs/raylib/raylib-6.0_win64_mingw-w64

# Define compiler flags
CFLAGS = -I"$(RAYLIB_PATH)/include" -Iinclude -Isrc/map -Isrc/player -Isrc/enemy -Isrc/collision -Isrc/save

# Define linker flags
LDFLAGS = -L"$(RAYLIB_PATH)/lib"

# Define libraries to link
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Define the target executable
TARGET = main.exe

all: # main.exe depends on main.o
	$(CC) $(CFLAGS) -g src/main.c src/map/map.c src/player/player.c src/enemy/enemy.c src/collision/collision.c src/save/save.c src/game_state/game_state.c src/menu/menu.c src/points/points.c src/ranking/ranking.c -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	./$(TARGET)