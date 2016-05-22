#include<cstdio>
int gcd(int a, int b) {
  while ((a%=b)&&(b%=a));
  return a + b;
}
const int N = 105;
int s[N];
main() {
  int i, j, k, n;
  for (i = 1; i <= 100; ++i)
    for (j = 1; j <= 100; ++j) {
      n = i;
      if (n < j) n = j;      
      for (k = 1; k <= 100; ++k) {        
        if (gcd(i, gcd(j, k)) != 1) continue;
        if (n < k) n = k;
        ++s[n];
      }
      if (gcd(i, j) != 1) continue;
      n = i;
      if (n < j) n = j;      
      s[n] += 3;      
  }
  s[1] += 3; 
  for (i = 1; i <= 100; ++i)
    s[i] += s[i-1];
  scanf("%d", &i);  
  while (i--) {
    scanf("%d", &n);
    printf("%d\n", s[n]);
  }
}
