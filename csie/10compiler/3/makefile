c: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -o c -ll
y.tab.h:	c.y
	yacc -d c.y
y.tab.c:	c.y
	yacc -d c.y	
lex.yy.c:	c.l y.tab.h
	lex $<
