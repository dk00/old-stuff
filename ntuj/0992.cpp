#include <stdio.h>

int ask(int a, int b, int c){
  printf("%d %d %d\n", a, b, c);
  fflush(stdout);
  int ret;
  scanf("%d",&ret);
  return ret;
}

void getmax(int *u1, int *u2, int v1, int v2)
{
  int r1, r2, r3;
  r1 = ask(*u1, *u2, v1);
  r2 = ask(*u1, *u2, v2);
  r3 = ask(*u1, v1, v2);
  if (r1 == r2) {
    if (r3 > r1) {
      *u1 = v1;
      *u2 = v2;
    } //else 
  } else if (r1 == r3){
    if (r1 > r2) {
      *u2 = v1;
    } else {
      *u1 = v2;
    }
  } else if (r2 == r3){
    if (r1 > r2) {
      *u1 = v1;
    } else {
      *u2 = v2;
    }
  }
 
}

void getmin(int *u1, int *u2, int v1, int v2)
{
  int r1, r2, r3;
  r1 = ask(*u1, *u2, v1);
  r2 = ask(*u1, *u2, v2);
  r3 = ask(*u1, v1, v2);
  if (r1 == r2) {
    if (r3 < r1) {
      *u1 = v1;
      *u2 = v2;
    } //else 
  } else if (r1 == r3){
    if (r1 < r2) {
      *u2 = v1;
    } else {
      *u1 = v2;
    }
  } else if (r2 == r3){
    if (r1 < r2) {
      *u1 = v1;
    } else {
      *u2 = v2;
    }
  }
}

int main(void)
{
  int n, i;
  while(scanf("%d",&n)!=EOF)
  {
    if(n==3) {
      printf("OK 1 2 3\n");
      fflush(stdout);
      continue;
    }
    int u1 = 1, u2 = 2;
    int v1 = 1, v2 = 2;
    //TODO odd number.
    for (i=3;i<n;i+=2){
      getmin(&u1, &u2, i, i+1);
    }
    if(n%2==1) {
      for (i=1;i<n;i++)
        if(i!=u1 && i!=u2)
          break;
      getmin(&u1, &u2, i, n);
    }
    
    for (i=3;i<n;i+=2){
      getmax(&v1, &v2, i, i+1);
    }
    if(n%2==1){
      for(i=1;i<n;i++)
        if(i!=v1 && i!=v2)
          break;
      getmax(&v1, &v2, i, n);
    }
    int arr[205];
    arr[u1] = 1;
    arr[u2] = 2;
    arr[v1] = n-1;
    arr[v2] = n;
    for(i=1;i<=n;i++)
      if(i!=u1 && i!=u2 && i!=v1 && i!=v2){
        arr[i] = ask(u1, v1, i);
      }
    printf("OK");
    for(i=1;i<=n;i++)
      printf(" %d", arr[i]);
    printf("\n");
    fflush(stdout);
  }
}
