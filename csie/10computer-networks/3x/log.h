#ifndef _LOG_H
#define _LOG_H
#include<vector>
using namespace std;
class LogWriter {
public:
  LogWriter();
  LogWriter& operator+=(const char name[]);
  int printf(const char format[], ...);
  ~LogWriter();
private:
  vector<FILE *> fp;
};
#endif
