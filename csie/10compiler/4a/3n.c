{
  int n, a;
  scan(n);
  a = n;
  {
    int n;
    n = a;    
    while (1 > 0) {
      if (n/2*2 == n) {
        n = n/2;
      }
      else {
        n = 3*n + 1;
      }
      print(n);
      if (n == 1) {
        break;
      }
    }
  }
  print(n);
}
