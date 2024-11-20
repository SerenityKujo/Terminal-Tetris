CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LDFLAGS=
EXEC=tetris
OBJ= $(patsubst %.c,%.o,$(wildcard *.c))

all:$(EXEC)

tetris: $(OBJ) 
	$(LD) -o tetris $(OBJ) $(LDFLAGS)

tetris-main.o: tetris-main.c
	$(CC) -c tetris-main.c -o tetris-main.o $(CFLAGS)

skins.o: skins.h skins.c
	$(CC) -c skins.c -o skins.o $(CFLAGS)

charMatrix.o: charMatrix.h charMatrix.c
	$(CC) -c charMatrix.c -o charMatrix.o $(CFLAGS)

playfield.o: playfield.h playfield.c
	$(CC) -c playfield.c -o playfield.o $(CFLAGS)

tetromino.o: tetromino.h tetromino.c
	$(CC) -c tetromino.c -o tetromino.o $(CFLAGS)

utilities.o: utilities.h utilities.c
	$(CC) -c utilities.c -o utilities.o $(CFLAGS)

tetris.o: tetris.h tetris.c
	$(CC) -c tetris.c -o tetris.o $(CFLAGS)

clean:
	rm -rf *.o tetris tetris.tar.gz

archive:
	tar -zcvf tetris.tar.gz *.h *.c skinfile.txt makefile

