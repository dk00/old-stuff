#include<cstdio>
struct node {
  int id;
  node *ch[26];
};
void init(node *& p) {
  p->id = -1;
  for (int i = 0; i < 26; ++i)
    p->ch[i] = NULL;
}
void build(int id, char a[], node *p = root) {
  if (!p->ch[a[0]])
    Init(p->ch[a[0]]);
  if (a[1]) build(id, a+1, p->ch[a[0]]);
  else p->id = id;
}
set<int> H;
void go(char a[], int e, node *p = root) {
  if (p->id >= 0 && !H.count(p->id))
    H.insert(p->id);
  if (p->ch[a[0]-'a'])
    go(a+1, e, p->ch[a[0]-'a']);
  if (e > 0) {
    go(a+1, e-1, p);

  }
}
main() {
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i)
      scanf("%s", tmp);
    tmp[12] = 0;
    build(i, tmp);
    scanf("%d", &n);
    while (n--) {
      scanf("%s %d", tmp, &i);
      H.clear();
      go(tmp, i);
      printf("%d\n", H.size());
    }
  }
}
