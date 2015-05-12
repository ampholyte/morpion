CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -std=gnu99 -g `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`

EXEC = morpion

HEADER += 

OBJ += morpion.o
	

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	@rm -rf *.o
	@rm -rf *.core
	@rm -rf $(EXEC)

