#include<cstdio>
char open[8], dom[57];
int sum, ub, spin;
int go(int v) {
  if (v >= 56) return 0;
  int max = 0, tmp;
  if (open[dom[v]]) {
    --open[dom[v]];
    sum -= dom[v];
    ++open[dom[v+1]];
    sum += dom[v+1];
    tmp = go(v+2);
    if (tmp > max) max = tmp;
    ++open[dom[v]];
    sum += dom[v];
    --open[dom[v+1]];
    sum -= dom[v+1];
  }
  if (open[dom[v+1]]) {
    --open[dom[v+1]];
    sum -= dom[v+1];
    ++open[dom[v]];
    sum += dom[v];
    tmp = go(v+2);
    if (tmp > max) max = tmp;
    ++open[dom[v+1]];
    sum += dom[v+1];
    --open[dom[v]];
    sum -= dom[v];
  }
  return sum*!(sum%5) + max;
}
int go() {
  int i, tmp, max = 0;
  ub = 0;
  for (i = 0; i < 56; i += 2) {
    if (dom[i] == dom[i+1]) spin = dom[i];
    else spin = -1;
    sum = dom[i] + dom[i+1];
    ++open[dom[i]];
    ++open[dom[i+1]];
    tmp = sum*!(sum%5) + go(i+2);
    if (tmp > max) max = tmp;
    --open[dom[i]];
    --open[dom[i+1]];
  }
  return max;
}
main() {
  int i, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", dom);
    for (i = 0; dom[i]; ++i) dom[i] -= '0';
    for (i = 0; i < 8; ++i) open[i] = 0;
    printf("%d\n", go());
  }
}
