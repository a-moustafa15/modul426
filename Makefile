CC = gcc
SRC = $(wildcard *.c)
o = $(wildcard *.o)

INCLUDE = -Iinclude
LIBDEF = -pthread

OUTPUT = sensor

CFLAGS = -g -Os

all:
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC) -o $(OUTPUT) $(LIBDEF)

run:
	sudo ./sensor