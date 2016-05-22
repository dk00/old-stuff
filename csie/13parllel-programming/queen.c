#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAXN 20
int n;

/* print */
void print_solution(int position[])
{
  int i;
  for (i = 0; i < n; i++)
    printf("%3d", position[i]);
  putchar('\n');
}
/* ok */
int ok(int position[], int next, int test)
{
  int i;

  for (i = 0; i < next; i++)
    if (position[i] == test || 
       (abs(test - position[i]) == next - i))
      return 0;

  return 1;
}
/* queen */
void queen(int position[], int next)
{
  int test;
  if (next >= n) {
    print_solution(position);
    return;
  }
  for (test = 0; test < n; test++) 
    if (ok(position, next, test)) {
      position[next] = test;
      queen(position, next + 1);
    }
}
/* main */
int main (int argc, char *argv[])
{
  int position[MAXN];
  assert(argc == 2);
  n = atoi(argv[1]);
  assert(n <= MAXN);
  queen(position, 0);
}
/* end */
