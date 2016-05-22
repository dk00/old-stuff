#include<ctime>
#include<cstdio>
#include<unistd.h>
main() {
  clock_t t = clock();
  printf("%d\n", t);
//  sleep(3);
  for (t = 0; t < 40000000;++t);
  printf("%d\n", clock());

}
