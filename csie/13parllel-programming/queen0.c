#include "omp.h"
#include <stdio.h>

#define N 12

int position[N];

void print_solution(int position[])
{
  int i;
  for (i = 0; i < N; i++)
    printf("%3d", position[i]);

  putchar('\n');
}

int ok(int position[], int next, int test)
{
  int i;

  for (i = 0; i < next; i++)
    if (position[i] == test || (abs(test - position[i]) == next - i))
      return 0;

  return 1;
}

void queen(int position[], int next)
{
  int test;

  if (next >= N) {
    print_solution(position);
    return;
  }

  for (test = 0; test < N; test++) 
    if (ok(position, next, test)) {
      position[next] = test;
      queen(position, next + 1);
    }
}


int main(int argc, char *argv[])
{
  int i;

  queen(position, 0);
}

