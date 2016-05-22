#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M = 16, N = 9999;
struct Processor {
  int bind, n, id[M];
  bool operator<(Processor p) const { 
    return n > p.n; 
  }
} P[M];

struct Task {
  long long req;
  int id, n, assign, cut;
  bool operator<(Task t) const {
    if (cut != t.cut) return cut < t.cut;
    return req > t.req;
  }
} t[N];

int n, m;
long long rem;
void read_conf() {
  int i, j;
  for (i = 0; scanf("%d", &P[i].n) == 1 && P[i].n > 0; ++i)
    for (j = 0; j < P[i].n; ++j) {
      scanf("%d", &P[i].id[j]);
      P[i].bind = -1;
    }
  m = i;
  sort(P, P+m);
  scanf("%d %lld", &n, &rem);
  for (i =0 ; i < n; ++i) {
    t[i].id = i;
    t[i].cut = -1;
    scanf("%d %lld", &t[i].n, &t[i].req);
  }
}


inline void nsleep(long long t) {
  timespec ts, rem;
  ts.tv_sec = t/1000000000;
  ts.tv_nsec = t%1000000000;
  nanosleep(&ts, &rem);
}

void assign() {
  int i, j, k;
  char cmd[99];
  for (i = 0; i < n; ++i) {
    if (t[i].assign < 0) continue;
    printf("%d(%lld): %d(%d)\n", t[i].id, t[i].req, t[i].assign, P[t[i].assign].n);
  }
  for (i = 0; i < n; ++i) {
    if (t[i].assign < 0) continue;
    k = t[i].assign;
    for (j = 0; j < t[i].n; ++j) {
      sprintf(cmd, "xl vcpu-pin %d %d %d", t[i].id, j, P[k].id[j%P[k].n]);
      puts(cmd);
    }
  }
  puts("");
}

inline bool geq(Processor P, Task t) { return P.n*rem >= t.req; }
inline bool eq(Processor P, Task t) { return geq(P, t) && P.n*(rem-1) < t.req; }

inline long long Div(long long a, int b) { return (a+b-1)/b; }

void schedule() {
  int i, j, k;
  long long t0, next;
  puts("init");
  while (1) {
    sort(t, t+n);
    if (t[0].req < 1) break;
    for (i = 0; i < n; ++i) {
      t[i].assign = t[i].cut;
      for (j = 0; j < m; ++j)
        if (P[j].bind < 0 && eq(P[j], t[i])) {
          P[j].bind = i;
          t[i].assign = t[i].cut = j;
        }
    }
    sort(t, t+n);
    for (i = j = 0; j < m; ++j) {
      if (i >= n || t[i].cut >= 0) break;
      if (P[j].bind >= 0) continue;
      t[i++].assign = j;
    }
    next = rem;
    for (i = 0; i < n; ++i) {
      if (t[i].cut >= 0) continue;
      if (t[i].assign >= 0) {
        k = P[t[i].assign].n;
        t0 = Div(t[i].req, k);
        printf("%lld %lld %d\n", t0, t[i].req, k);
      }
      if (t0 < next || next < 0)
        next = t0;
      for (j = 0; j < m; ++j) {
        if (P[j].bind >= 0) continue;
        t0 = P[j].n*rem - t[i].req;
        k = (P[j].n - (t[i].assign < 0? 0: P[t[i].assign].n));
        if (k == 0) continue;
        t0 /= k;
        if (t0 < next || next < 0)
          next = t0;
      }
    }
    for (i = 0; i < n; ++i) {
      if (t[i].cut >= 0)
        t[i].req -= P[t[i].cut].n*next;
      else if (t[i].assign >= 0) 
        t[i].req -= P[t[i].assign].n*next;
    }
    printf("> next event: %lld\n", next);
    assign();
    rem -= next;
    if (rem > 0) nsleep(next);
    else break;
  }
}

main() {
  read_conf();
  schedule();
}
