#!/usr/bin/make

CC = g++
SRC = expression-validator.cpp
PROG = expression-validator.out

build: clean $(PROG)

clean:
	rm -f $(PROG)

$(PROG): $(SRC)
	$(CC) $(SRC) -o $(PROG)
