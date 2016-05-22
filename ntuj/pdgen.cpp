#include <stdio.h>
#include <stdlib.h>

int main(void){
  int i;
  printf("1000\n");
  for(i=0;i<1000;i++) {
    int k=rand()%100000+1;
    int x=rand()%1000000, y=rand()%100000;
    printf("%d %d %d %d\n", x, y, x+k, y+k);
  }
  puts("0");
  return 0;
}
