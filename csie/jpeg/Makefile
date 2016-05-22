all: dec

dec: dec.cpp format.cpp huffman.cpp dct.cpp bmp.cpp common.h
	$(CXX) format.cpp huffman.cpp dct.cpp bmp.cpp $< -O3 -o $@

%: %.cpp
	$(CXX) $< -o $@
