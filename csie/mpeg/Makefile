all: dec

dec: window.cpp dec.cpp dct.cpp vlc.cpp common.h data.h 
	$(CXX) window.cpp vlc.cpp dct.cpp dec.cpp -o $@ -mwindows -mconsole -lopengl32 -lglu32 -O3

%: %.cpp
	$(CXX) $< -o $@ -mwindows -mconsole -lopengl32 -lglu32 
