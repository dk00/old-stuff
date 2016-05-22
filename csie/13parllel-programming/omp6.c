#include<stdio.h>
int N;
struct State {
  int col[99], d0[99], d1[99];
};
int set(int r, int c, struct State *s) {
  if (s->col[c] || s->d0[r+c] || s->d1[N+r-c])
    return 0;
  s->col[c]++;
  s->d0[r+c]++;
  s->d1[N+r-c]++;
  return 1;
}
void unset(int r, int c, struct State *s) {
  s->col[c]--;
  s->d0[r+c]--;
  s->d1[N+r-c]--;
}
int q(int r, struct State *s) {
  
  if (r >= N) return 1;
  int c, sum = 0;
  for (c = 0; c < N; c++) {
    if (set(r, c, s)) {
      sum += q(r+1, s);
      unset(r, c, s);
    }
  }
  return sum;
}
int main() {
  int i, j, count[N];
  struct State s;
  scanf("%d", &N);
  #pragma omp parallel for private(s, j)
  for (i = 0; i < 14; i++) {
    if (i >= N/2) continue;
    for (j = 0; j < N*2; ++j)
      s.col[j] = s.d0[j] = s.d1[j] = 0;
    set(0, i, &s);
    count[i] = q(1, &s);
    unset(0, i, &s);
  }
  for (i = 0; i < N/2; ++i)
    printf("%d ", count[i]);
  return 0;
}

