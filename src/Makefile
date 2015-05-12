CC = g++
CFLAGS = -W -Wall -Wextra -pedantic -Wpointer-arith -g `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`

EXEC = morpion

HEADER += defines.h
HEADER += main.h
HEADER += object.h
HEADER += game.h
HEADER += engine.h
HEADER += menu.h
HEADER += ia.h

OBJ += main.o
OBJ += object.o
OBJ += game.o
OBJ += engine.o
OBJ += menu.o
OBJ += ia.o
	

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADER)
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	@rm -rf *.o
	@rm -rf *.core
	@rm -rf $(EXEC)

