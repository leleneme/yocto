CC=gcc

# Get a list of all source files from src/ dir (using wildcard function)
SRC=$(wildcard src/*.c)

OUTDIR=bin/

# Commom compiler flags
CFLAGS=-Wall -Wextra -pedantic --std=c99

# Release (Optimization level 2)
yocto : $(SRC)
	$(CC) -o $(OUTDIR)$@ $^ $(CFLAGS) $(LIBS) -O2

# Debug (To be used with GDB)
debug: $(SRC)
	$(CC) -o $(OUTDIR)$@ $^ $(CFLAGS) $(LIBS) -g

clean:
	rm -rf bin/yocto bin/*.o *.o
