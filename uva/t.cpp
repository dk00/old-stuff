#include<cstdio>
int s[9999];
main() {
  int i, j;
  for (i = 1; i < 30; i++)
    for (j = i+1; j < 30; j++) {
      s[i*i + j*j]++;
      if (i*i + j*j == 85)
        printf("%d %d\n", i, j);
    }
  for (i = 0; i < 29*29; i++)
    if (s[i] > 0)
      printf("[%d %d]", i, s[i]);
  
}
