CPP=g++
CPPFLAGS=-O3

all: blitz

blitz: blitz.h color.h blitz1.cpp interface.o
	$(CPP) blitz1.cpp interface.o -lgdi32 -o blitz $(CPPFLAGS)

%.o: %.cpp blitz.h
	$(CPP) -c $< $(CPPFLAGS)
