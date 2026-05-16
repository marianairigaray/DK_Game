# Define the compiler
CC = gcc

# Define raylib path
RAYLIB_PATH = ./libs/raylib/raylib-6.0_win64_mingw-w64

# Define compiler flags
CFLAGS = -I"$(RAYLIB_PATH)/include" -Iinclude

# Define linker flags
LDFLAGS = -L"$(RAYLIB_PATH)/lib"

# Define libraries to link
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Define the target executable
TARGET = main.exe

all: # main.exe depends on main.o
	$(CC) $(CFLAGS) -g src/main.c src/map/map.c src/collision/collision.c src/player/player.c src/enemy/enemy.c -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	./$(TARGET)