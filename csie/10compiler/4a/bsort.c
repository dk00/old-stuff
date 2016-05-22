{
  int[3][999] s;
  int i,j,k,n;
  scan(n);
  i = 0;
  while (i < n) {
    scan(s[1][i]);
    i = i + 1;
  }
  print(n);
  i = 0;
  while (i < n) {
    j = 1;
    while (j < n) {
      if (s[1][j] < s[1][j-1]) {
        k = s[1][j];
        s[1][j] = s[1][j-1];
        s[1][j-1] = k;
      }
      j = j + 1;
    }
    i = i + 1;
  }
  i = 0;
  while (i < n) {
    print(s[1][i]);
    i = i + 1;
  }
}
