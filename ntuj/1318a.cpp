#include<cstdio>
main() {
  int i, j, n, sum, T, num[4];
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sum = 0;
    for (j = 0; j < 5; ++j)
      num[j] = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      if (j % 10 < 5)
        ++num[j%10];
      sum += j - (j+5)/10;
    }
    while ((num[1] > 0 && num[4] > 0) || (num[2] > 0 && num[3] > 0)) {
      if (num[1] > 0 && num[4] > 0)
        --num[1], --num[4], --sum;
      else
        --num[2], --num[3], --sum;
    }
    while (num[1] + num[4] + num[2] + num[3] > 0) {
      if (num[1] >= 2 && num[3] > 0) {
        num[1] -= 2, --num[3], --sum;
        continue;
      }
      if (num[1] >= 1 && num[2] > 1) {
        --num[1], num[2] -= 2, --sum;
        continue;
      }
      if (num[2] >= 3) {
        sum += num[2]/3;
        num[2] %= 3;
      }      
      if (num[1] >= 3 && num[2] > 0) {
        num[1] -= 3, --num[2], --sum;
        continue;
      }
      if (num[2] > 0 && num[4] > 0) {
        --num[2], --num[4], --sum;
        continue;
      }
      if (num[3] > 1) {
        sum -= num[3]/2;
        num[3] %= 2;
        continue;
      }
      if (num[3] > 0 && num[4] > 0) {
        --num[3], --num[4], --sum;
        continue;
      }
      if (num[3] > 0) num[3] = 0;
      if (num[4] > 0) {
        sum -= num[4]/2;
        num[4] = 0;
      }
      if (num[1] > 0) {
        sum -= num[1]/5;
        num[1] = 0;
      }
      if (num[2] > 0) {
        sum -= num[2]/3;
        num[2] = 0;
      }
    }
    //XXX
    printf("%d\n", sum);
  }
}

/*
 1 4
 2 3
 1 1 3
 1 2 2
 1 1 1 2
 1 1 1 1 1
 2 4
 2 2 2
 3 3
 3 4
 4 4
*/
