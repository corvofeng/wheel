
CC := g++
OBJ := RBTree.o main.o
BIN := main
CFLAGS := -g
CXXFLAGS := -g


all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN)


RBTree.o: RBTree.cpp RBTree.h

main.o: main.cpp RBTree.h

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN)
