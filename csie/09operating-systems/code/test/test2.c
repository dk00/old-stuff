/* test2.c
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
  
  for (i = 1; i <= MAX_NUM; i++) {
    SimplePrint("test2:%d ", i);
    result[i-1] = i-1;
    if ((i % 5) == 0)
      SimplePrint("\n", i);
  }
  SimplePrint("*************** End of test2 *****************\n\n", i);
}
