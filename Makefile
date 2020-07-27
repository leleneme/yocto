CC=gcc
SRC=$(wildcard src/*.c)

OUTDIR=bin/

CFLAGS=-Wall -Wextra -pedantic --std=c99 -g

yocto : $(SRC)
	$(CC) -o $(OUTDIR)$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf bin/yocto bin/*.o *.o
