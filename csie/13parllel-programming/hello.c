#include <stdio.h>
/* print */
void PrintHello(int id)
{
  printf("Hello World! It's me, id #%d!\n", 
	 id);
}
/* main */
#define NUM_ID 8
int main (int argc, char *argv[])
{
  int t;
  for(t = 0; t < NUM_ID; t++){
    printf("In main: loop t = %d\n", t);
    PrintHello(t);
  }
  return 0;
}
/* end */
