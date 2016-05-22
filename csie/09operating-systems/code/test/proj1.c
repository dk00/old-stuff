/* proj1.c
 *	Sample test file for the project 1
 *
 */

#include "syscall.h"

#define NUM 5

int
main()
{
  int result;
  int id[NUM];
  int i;
  
  result = Add(42, 23);
  SimplePrint("The result of Add(42, 23) is %d!\n\n", result);
  SimplePrint("%dTest%d\n",1);
  SimplePrint("%d",2);
  SimplePrint("%d%d\n",3);

  for (i = 0; i < NUM; i++)
      id[i] = CreateThreads();

  SetPriority(id[0], 3);
  SetPriority(id[1], 2);
  SetPriority(id[2], 5);
  SetPriority(id[3], 6);
  SetPriority(id[4], 4);

  SetPriority(0, 100);
  SetPriority(0, 0);
  for (i = 0; i < NUM; i++)
      id[i] = CreateThreads();

  SetPriority(id[0], 3);
  SetPriority(id[1], 2);
  SetPriority(id[2], 5);
  SetPriority(id[3], 6);
  SetPriority(id[4], 4);

  SetPriority(0, 100);
  SetPriority(id[3], 60);
  SetPriority(-5, 6);
  Halt();
  /* not reached */
}
