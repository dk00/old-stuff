c: y.tab.cpp lex.yy.o
	g++ y.tab.cpp lex.yy.o -o c -ll
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c:	c.l y.tab.hpp
	lex $<
y.tab.hpp:	c.y
	yacc -d c.y -o y.tab.cpp
y.tab.cpp:	c.y
	yacc -d c.y	-o y.tab.cpp
