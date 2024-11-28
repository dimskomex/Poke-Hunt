# Paths
INCLUDE = ../include
SRC = ../src

# Compiler
CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -I$(INCLUDE) $(LDFLAGS)
LDFLAGS = -lm -lraylib

OBJS = game.o $(SRC)/state.o $(SRC)/interface.o $(SRC)/updates.o $(SRC)/collisions.o $(SRC)/UsingLinkedList/ADTList.o $(SRC)/UsingDynamicArray/ADTVector.o $(SRC)/create.o $(SRC)/probabilities.o

EXEC = game

ARGS =

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC) valgrind-out.txt

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXEC) $(ARGS)