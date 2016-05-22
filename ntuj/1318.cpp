#include<cstdio>
main() {
  int i, j, k, n, sum, T, num[100];
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
    if (num[3] && num[4]) {
      sum -= (num[3] + num[4])/2;
      num[3] = num[4] = 0;
    }
    if (num[2] && num[4]) {
      j = num[2]<num[4]?num[2]:num[4];
      num[2] -= j;
      num[4] -= j;
      sum -= j;
    }
    if (num[1] && num[3]) {
      j = num[1]/2<num[3]?num[1]/2:num[3];
      num[1] -= j*2;
      num[3] -= j;
      sum -= j;
    }
    if (num[1] && num[2]) {
      int best = 0;
      for (k = 0; k*2 <= num[1] && k <= num[2]; ++k) {    
        num[1] -= k*2;
        num[2] -= k;
        j = num[1]/3<num[2]?num[1]/3:num[2];
        num[1] -= j*3;
        num[2] -= j;
        if (j + k + num[1]/5 + num[2]/3 > best)
          best = j + k + num[1]/5 + num[2]/3;
        num[1] += j*3;
        num[2] += j;
        num[1] += k*2;
        num[2] += k;        
      }
      sum -= best;
      num[1] = num[2] = 0;
    }
    for (i = 1; i <= 4; ++i)
      sum -= num[i]/((5+i-1)/i);
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
