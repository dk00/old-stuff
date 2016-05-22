all: search
CFLAGS = -O3
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
CFLAGS += -lrt
endif
SRC = search_core.cpp game.cpp interface.cpp
INC = game.h interface.h
%: %.cpp $(SRC) $(INC)
	$(CXX) -o $@ $< $(SRC) $(CFLAGS)
