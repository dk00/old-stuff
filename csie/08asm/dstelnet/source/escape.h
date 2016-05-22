#ifndef ESCAPE_H
#define ESCAPE_H
#include<iostream>
#include<string>
#include"text.h"
using namespace std;
#define ESCAPE_OK 0
#define ESCAPE_NO 1
#define ESCAPE_ERROR 2
class Escape{
	public:
	int operator()(Screen &sc,const char *seq);
	private:
	Screen *sc;
	const char *seq;
	int num[10],top;
	int start();
	int end();
};
extern Escape escape;
#endif
