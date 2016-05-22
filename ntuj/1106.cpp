#include<cstdio>
#include<cstring>
const int N = 200, M = 27, L = 99;
struct node {
  int id, count;
  node *back, *ch[M];
} *root;
inline void init(node *&ptr) {
  ptr = new node;
  ptr->id = -1;
  ptr->count = -1;
  for (int i = 0; i < M; ++i) ptr->ch[i] = NULL;
  ptr->back = root;
}
void clear(node *ptr) {
  if (ptr == NULL) return;
  for (int i = 0; i < M; ++i) clear(ptr->ch[i]);
  delete ptr;
}
void build(char a[], node *ptr = root) {
  if (!a[0]) return;
  char c = a[0] - 'a';
  if (!ptr->ch[c]) init(ptr->ch[c]);
  build(a+1, ptr->ch[c]);
}
inline void next(node *&ptr, char a) {
  while (ptr != root && !ptr->ch[a]) ptr = ptr->back;
  if (ptr->ch[a]) ptr = ptr->ch[a];
}
node *p[N*L], *p0[N], *p1[N];
int pn, num[N], len[N], same[N];
void init(int n, char s[][L]) {
  int i, j, m;
  init(root);
  for (i = pn = m = 0; i < n; ++i) {
    len[i] = strlen(s[i]);
    if (len[i] > m) m = len[i];
    build(s[i]);
    p1[i] = root;
    p[pn] = p0[i] = root->ch[s[i][0]-'a'];
    if (p[pn]->count < 0) p[pn++]->count = 0;
    p0[i]->back = p1[i];
  }
  for (j = 1; j < m; ++j)
    for (i = 0; i < n; ++i) {
      if (j >= len[i]) continue;
      next(p1[i], s[i][j]-'a');
      p[pn] = p0[i] = p0[i]->ch[s[i][j]-'a'];
      if (p[pn]->count < 0) p[pn++]->count = 0;
      p0[i]->back = p1[i];
    } 
  for (i = 0; i < n; ++i)
    if (p0[i]->id < 0) same[i] = p0[i]->id = i;
    else same[i] = p0[i]->id;
}
void match(char t[]) {
  node *ptr = root;
  for (int i = 0; t[i]; ++i) {
    next(ptr, t[i]-'a');
    ++ptr->count;
  }
  for (int i = pn - 1; i >= 0; --i) {
    if (p[i]->back) p[i]->back->count += p[i]->count;
    if (p[i]->id >= 0) num[p[i]->id] = p[i]->count;
  }
}
char s[N][99], t[1010000];
main() {
  int i, j, n;
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; ++i)
      scanf("%s", s[i]);
    init(n, s);
    scanf("%s", t);
    match(t);
    for (i = j = 0; i < n; ++i)
      if (num[same[i]] > j) j = num[i];
    printf("%d\n", j);
    for (i = 0; i < n; ++i)
      if (num[same[i]] == j) puts(s[i]);
    clear(root);
  }
}
