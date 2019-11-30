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

install: 
	make
	sudo cp sensorApp /usr/bin/
	sudo cp sensorApp.service /etc/systemd/system/
	sudo systemctl daemon-reload

uninstall:
	sudo systemctl stop sensorApp.service
	sudo rm /usr/bin/sensorApp
	sudo rm /etc/systemd/system/sensorApp.service

free:
	echo 14 > /sys/class/gpio/unexport
	echo 15 > /sys/class/gpio/unexport
	echo 18 > /sys/class/gpio/unexport
	echo 23 > /sys/class/gpio/unexport