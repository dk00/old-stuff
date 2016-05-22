/* test1.c
 *	Sample test program of project3
 *
 */

#include "syscall.h"

int
main()
{
  const int MAX_NUM = 100;
  int result[MAX_NUM];
  int i;
  
  for (i = 0; i < MAX_NUM; i+=10) {
    SimplePrint("test1:%d ", i);
    SimplePrint("test1:%d ", i+1);
    SimplePrint("test1:%d ", i+2);
    SimplePrint("test1:%d ", i+3);
    SimplePrint("test1:%d ", i+4);
    SimplePrint("\n", i);
    SimplePrint("test1:%d ", i+5);
    SimplePrint("test1:%d ", i+6);
    SimplePrint("test1:%d ", i+7);
    SimplePrint("test1:%d ", i+8);
    SimplePrint("test1:%d ", i+9);
    SimplePrint("\n", i);
  }
  result[49] = 49;
  result[99] = 99;
  SimplePrint("*************** End of test1 *****************\n\n", i);
}
