CC=g++
CCXFLAGS=-g -std=c++14 -Wall

OBJS= src/main.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o p2 ${OBJS}

.PHONY: clean

run: all
	./p2 input.txt
	
clean: 
	rm -rf src/*.o p2 output.txt