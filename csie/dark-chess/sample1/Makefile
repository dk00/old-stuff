LDFLAGS=-static -s
.PHONY:	clean
search.exe:	main.cc anqi.cc
	$(CXX) -o $@ $^ $(LDFLAGS)
clean:
	DEL search.exe 2>NUL
