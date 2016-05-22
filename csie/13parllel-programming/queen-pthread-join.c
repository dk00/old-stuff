/* declaration */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 20
int n;

int position[MAXN];
/* print */
void print_solution(int position[])
{
  int i;
  char string[MAXN];
  for (i = 0; i < n; i++)
    string[i] = position[i] + '0';
  string[n] = '\0';
  puts(string);
}
/* ok */
int ok(int position[], int next, int test)
{
  int i;

  for (i = 0; i < next; i++)
    if (position[i] == test || (abs(test - position[i]) == next - i))
      return 0;

  return 1;
}
/* queen */
void queen(int position[], int next)
{
  int test;

  if (next >= n) {
    position[n]++;
    print_solution(position);
    return;
  }
  for (test = 0; test < n; test++) 
    if (ok(position, next, test)) {
      position[next] = test;
      queen(position, next + 1);
    }
}
/* go */
void *goqueens(void *pos)
{
  int position[MAXN];
  position[0] = (long)pos;
  position[n] = 0;
  queen(position, 1);
  pthread_exit(position[n]);
}
/* main */
int main (int argc, char *argv[])
{
  pthread_t threads[MAXN];
  int i, error;

  assert(argc == 2);
  n = atoi(argv[1]);
  assert(n <= MAXN);
  /* join */
  void *status;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, 
    PTHREAD_CREATE_JOINABLE);
  for(i = 0; i < n; i++) {
    error = pthread_create(&threads[i], &attr, 
			   goqueens, (void *)i);
    assert(error == 0);
  }
  pthread_attr_destroy(&attr);
  int count = 0;
  for (i = 0; i < n; i++) {
    pthread_join(threads[i], &status);
    printf("thread done(%d)\n", (int)status);
    count += (int)status;
  }
  printf("Total number of solutions: %d\n", count);
  pthread_exit(NULL);
}
/* end */
