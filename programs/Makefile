LIB = ../lib

game_OBJS = game.o $(MODULES)/state.o $(MODULES)/interface.o $(MODULES)/updates.o $(MODULES)/UsingLinkedList/ADTList.o $(MODULES)/UsingDynamicArray/ADTVector.o $(LIB)/libraylib.a

# Parameters of the raylib library
include $(LIB)/libraylib.mk

# To build libraylib.a we run the make on the lib directory.
$(LIB)/%.a:
	$(MAKE) -C $(LIB) $*.a

# The body of the Makefile
include ../common.mk