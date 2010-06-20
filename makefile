source=iTunesDB.cpp db.cpp unicode.cpp 
header=db.h unicode.h iTunesDB.h iTunesDB_default.h
parser=y.tab.cpp lex.yy.o
all: main
main: main.cpp $(source) $(header) $(parser)
	g++ main.cpp $(source) $(parser) -ll -o main -std=c++0x -std=c++0x
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: pro.l y.tab.hpp
	flex pro.l
y.tab.cpp: pro.y
	yacc -d pro.y -o y.tab.cpp
y.tab.hpp: pro.y
	yacc -d pro.y -o y.tab.cpp
test: test.cpp $(source) $(header)
	g++ test.cpp debug.cpp $(source) -o test -std=c++0x -DDEBUG -g
svn: $(source) $(header) $(parser)
	svn add $(source) $(header) $(parser)
