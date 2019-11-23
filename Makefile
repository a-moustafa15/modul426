CC = gcc
SRC = $(wildcard *.c)
o = $(wildcard *.o)

INCLUDE = -Iinclude
LIBDEF = -pthread

OUTPUT = sensorApp

CFLAGS = -g -Os

all:
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC) -o $(OUTPUT) $(LIBDEF)

run:
	sudo ./$(OUTPUT)