#include<cstdio>
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n, dog, min, max;
    char tmp[99];
    scanf("%d", &j);
    for (n = dog = 0; j--;) {
      scanf("%s", tmp);
      if(tmp[0] == 'd') {
        if (dog) dog = 3;
        dog |= 1;
      }
      else if (tmp[0] == 'D') {
        if (dog) dog = 3;
        dog |= 2;
      }
      else {
        sscanf(tmp, "%d", &k);
        if (!n++)
          min = max = k;
        if (k < min) min = k;
        if (k > max) max = k;
      }
    }
    if (dog == 0 || n == 0 || dog == 3) {
      puts("SAFE");
      continue;
    }
    if (dog == 2) {
      printf("%d\n", max);
      continue;
    }
    if (dog == 1) {
      printf("%d\n", min);
      continue;
    }
    i/=0;
  }
}
