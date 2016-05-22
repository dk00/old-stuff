#include<set>
#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
set<int> H;
int n, m, rn[32], r0[16], r1[16], wr[16], val[16], next[16], p3[16];
char cmd[16][99];
inline void Add(int& v) {
  if (v < 0) return;
  if (rn[v] < 0) 
    rn[v] = m++;
  v = rn[v];
}
inline int GetReg(int k, int i) {
  if (i < 0) return 0;
  return k%p3[i+1]/p3[i];
}
inline int SetReg(int k, int i, int v) {
  return k - k%p3[i+1]/p3[i]*p3[i] + p3[i]*v;
}
inline int SetPC(int k, int v) {
  return k - k/p3[m]*p3[m] + p3[m]*v;
}
void print(int k) {
  printf("%s -> %d:", cmd[k/p3[m]], next[k/p3[m]]);
  for (int i = 0; i < m; ++i)
    printf(" %d", GetReg(k, i));
  puts("");
}
int exec(int pc, int k) {
  int ra = GetReg(k, r0[pc]) - 1, rb = GetReg(k, r1[pc]) - 1;
  k = SetPC(k, pc + 1);
  if (!strcmp(cmd[pc], "AND"))
    return SetReg(k, wr[pc], 1 + (ra&rb));
  if (!strcmp(cmd[pc], "OR"))
    return SetReg(k, wr[pc], 1 + (ra|rb));
  if (!strcmp(cmd[pc], "XOR"))
    return SetReg(k, wr[pc], 1 + (ra^rb));
  if (!strcmp(cmd[pc], "NOT"))
    return SetReg(k, wr[pc], 1 + (!ra));
  if (!strcmp(cmd[pc], "MOV"))
    return SetReg(k, wr[pc], 1 + (ra));
  if (!strcmp(cmd[pc], "SET"))
    return SetReg(k, wr[pc], 1 + val[pc]);
  if (!strcmp(cmd[pc], "RANDOM"))
    return SetReg(k, wr[pc], 0);
  if (!strcmp(cmd[pc], "JMP") || (!strcmp(cmd[pc], "JZ") && !ra))
    return SetPC(k, next[pc]);
  return k;
}
inline void pass(queue<int>& Q, int k) {
  if (H.count(k)) return;
  H.insert(k);
  Q.push(k);
}
void go(queue<int>& Q, int k) {
  int pc = k/p3[m], tmp;
  if (r0[pc] == 0 && !GetReg(k, r0[pc])) {
    for (int i = 1; i < 2; ++i) {
      pass(Q, exec(pc, SetReg(k, r0[pc], i)));
      if (r1[pc] == 0 && !GetReg(k, r1[pc])) {
        pass(Q, exec(pc, SetReg(k, r1[pc], 1)));
        pass(Q, exec(pc, SetReg(k, r1[pc], 2)));      
      }    
      else pass(Q, exec(pc, k));
    }
  }
  else {
    if (r1[pc] == 0 && !GetReg(k, r1[pc])) {
      pass(Q, exec(pc, SetReg(k, r1[pc], 1)));
      pass(Q, exec(pc, SetReg(k, r1[pc], 2)));
    }
    else pass(Q, exec(pc, k));
  }
}
main() {
  int i, j, k, C = 0;
  while (scanf("%d", &n) == 1) {
    H.clear();
    for (i = 0; i < 32; ++i)
      rn[i] = -1;
    m = 0;    
    for (i = 0; i < n; ++i) {
      scanf("%s", cmd[i]);
      next[i] = i + 1;
      r0[i] = r1[i] = wr[i] = -1;
      if (!strcmp(cmd[i], "XOR") || !strcmp(cmd[i], "AND") || !strcmp(cmd[i], "OR")
       || !strcmp(cmd[i], "SET") || !strcmp(cmd[i], "MOV") || !strcmp(cmd[i], "JZ")) {
        scanf("%d %d", &j, &k);
        if (!strcmp(cmd[i], "XOR") || !strcmp(cmd[i], "AND") || !strcmp(cmd[i], "OR"))
          r0[i] = wr[i] = j, r1[i] = k;
        if (!strcmp(cmd[i], "MOV")) 
          wr[i] = j, r0[i] = k;
        if (!strcmp(cmd[i], "JZ")) next[i] = j, r0[i] = k;
        if (!strcmp(cmd[i], "SET")) wr[i] = j, val[i] = k;
      }
      if (!strcmp(cmd[i], "NOT") || !strcmp(cmd[i], "RANDOM")
        || !strcmp(cmd[i], "JMP")) {
        scanf("%d", &j);
        if (!strcmp(cmd[i], "NOT"))
          r0[i] = wr[i] = j;
        else if (!strcmp(cmd[i], "RANDOM"))
          wr[i] = j;
        else next[i] = j;
      }
      Add(r0[i]);
      Add(r1[i]);
      Add(wr[i]);
    }
    for (p3[0] = i = 1; i <= m; ++i)
      p3[i] = p3[i-1]*3;
    queue<int> Q[2];
    Q[0].push(0);
    for (i = 0; !Q[i%2].empty(); ++i) {
      while (!Q[i%2].empty()) {
        j = Q[i%2].front();
        if (j/p3[m] == n - 1) {
          j = -1;
          break;
        } 
        Q[i%2].pop();
        go(Q[1-i%2], j);
      }
      if (j < 0) break;
    }
    if (C++) puts("");
    if (j < 0) printf("%d\n", 1 + i);
    else puts("HANGS");
  }
}
