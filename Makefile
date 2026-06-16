# Compiler
CC = gcc

# Sources
SRC = \
	src/main.c \
	src/map/map.c \
	src/player/player.c \
	src/enemy/enemy.c \
	src/collision/collision.c \
	src/save/save.c \
	src/game_state/game_state.c \
	src/menu/menu.c \
	src/points/points.c \
	src/ranking/ranking.c \
	src/menu/pause_menu.c \
	src/menu/button.c

# Includes
CFLAGS = \
	-Ilibs/raylib/src \
	-Iinclude \
	-Isrc/map \
	-Isrc/player \
	-Isrc/enemy \
	-Isrc/collision \
	-Isrc/save

# OS-specific settings
ifeq ($(OS),Windows_NT)

	TARGET = main.exe

	LDFLAGS = -Llibs/raylib/src

	LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

else

	TARGET = main

	LDFLAGS = -Llibs/raylib/src

	LDLIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

endif

all:
	$(CC) $(CFLAGS) -g $(SRC) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	./$(TARGET)

clean:
	rm -f main main.exe