#ifndef _IO_H
#define _IO_H
#include<string>
#include<cstdio>
using namespace std;

class Reader {
  FILE *fp;
public:
  bool end;
  bool init(const char *name);
  unsigned read(int bit);
  int close();
};

class Writer {
  FILE *fp;
public:
  bool init(const char *name);
  int write(const char symbol[]);
  int close();
};
#endif
