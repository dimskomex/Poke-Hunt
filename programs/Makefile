game_OBJS = game.o $(MODULES)/state.o $(MODULES)/interface.o $(MODULES)/updates.o $(MODULES)/collisions.o $(MODULES)/UsingLinkedList/ADTList.o $(MODULES)/UsingDynamicArray/ADTVector.o $(LIB)/libraylib.a $(MODULES)/create.o 

# Parameters of the raylib library
include ../lib/libraylib.mk

# To build libraylib.a we run the make on the lib directory.
../lib/%.a:
	$(MAKE) -C ../lib $*.a

# The body of the Makefile
include ../common.mk