#include<cstdio>
#include<string>
#include<vector>
using namespace std;
struct Char {
  int HP, MP, Speed, Damage[2], sDamage[2], Attack, sAttack, sCost, sType,
    aSP, dSP, nHP, nMP, SP;
  void read() {
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
      &HP, &MP, &Speed, &Damage[0], &Damage[1], &sDamage[0], &sDamage[1],
      &Attack, &sAttack, &sCost, &sType, &aSP, &dSP, &nHP, &nMP, &SP);
  }
} s[6];
int id[5], HealHP, HealMP, ItemMP;
struct State {
  int HP[5], MP[5], SP[5], CD[5], Act[5];
  int ready[5];
  void Init() {
    for (int i = 0; i < 5; ++i) {
      Act[i] = 0;
      HP[i] = s[id[i]].nHP;
      MP[i] = s[id[i]].nMP;
      SP[i] = s[id[i]].SP;
      CD[i] = 5 - s[id[i]].Speed;
    }
  }
  void Next() {
    for (int i = 0; i < 5; ++i)
      ready[i] = -1;
    for (int i = 0; i < 5; ++i)
      if (--CD[i] == 0) {
        ++Act[i];
        CD[i] = 5 - s[id[i]].Speed;
        ready[id[i]] = i;
      }
      else ready[id[i]] = -1;
  }
  void Attack(int a, int b) {
    SP[a] += s[id[a]].aSP;
    if (SP[a] > 100) SP[a] = 100;
    SP[b] += s[id[b]].dSP;
    if (SP[b] > 100) SP[b] = 100;
    if (a > 2) {
      HP[b] -= s[id[b]].Damage[a-3];
      return;
    }
    HP[b] -= s[id[a]].Attack;
    if (b == 3) HP[a] -= s[id[a]].Attack;
  }
  bool sAttack(int a) {
    if (a > 2) {
      for (int i = 0; i < 3; ++i)
        HP[i] -= s[id[i]].sDamage[a-3];
      return true;
    }
    if (SP[a] < s[id[a]].sCost) return false;
    SP[a] -= s[id[a]].sCost;
    HP[3] -= s[id[a]].sAttack;
    if (s[id[a]].sType == 1) HP[a] -= s[id[a]].sAttack;
    return true;
  }
  bool Heal(int a) {
    if (HP[a] >= s[id[a]].HP || MP[a] < HealMP) return false;
    MP[a] -= HealMP;
    HP[a] += HealHP;
    if (HP[a] > s[id[a]].HP)
      HP[a] = s[id[a]].HP;
    return true;
  }
  void Item(int a) {
    MP[a] += ItemMP;
    if (MP[a] > s[id[a]].MP)
      MP[a] = s[id[a]].MP;
  }
  void print() {
    for (int i = 0; i < 4; ++i)
      printf("%d ", HP[i]);
    puts("");
  }
} T[99];
int Limit;
bool Fight(int d = 0, int turn = 0, int i = 0) {
  if (turn >= Limit) return false;
  for (int j = 0; j < 3; ++j)
    if (T[d].HP[j] <= 0) return false;
  if (T[d].HP[3] <= 0) {
    T[d].print();
    return true;
  }
  if (i >= 5)
    return Fight(d, turn+1, 0);
  if (i == 0)
    T[d].Next();
  if (T[d].ready[i] < 0) return Fight(d, turn, i+1);
  if (T[d].ready[i] > 2) {
    if (T[d].Act[i]%4 == 0)
      T[d].sAttack(T[d].ready[i]);
    else
      T[d].Attack(T[d].ready[i], T[d].Act[i]%4 - 1);
    return Fight(d, turn, i+1);
  }  
  T[d+1] = T[d];
  T[d+1].Attack(T[d].ready[i], 3);
  if (Fight(d+1, turn, i+1)) {
    T[d].print();
    return true;
  }
  T[d+1] = T[d];
  if (T[d+1].sAttack(T[d].ready[i]) && Fight(d+1, turn, i+1)) {
    T[d].print();
    return true;
  }
  T[d+1] = T[d];
  if (T[d+1].Heal(T[d].ready[i]) && Fight(d+1, turn, i+1)) {
    T[d].print();
    return true;
  }
  T[d+1] = T[d];
  T[d+1].Item(T[d].ready[i]);
  if (Fight(d+1, turn, i+1)) {
    T[d].print();
    return true;
  }
}
vector<string> Team;
char used[4], Head[] = "HLMY";
void Choose(int d = 0) {
  if (d >= 3) {
    T[0].Init();
    if (Fight()) {
      string t = "";
      for (int i = 0; i < 3; ++i)
        t += Head[id[i]];
      Team.push_back(t);
      puts(t.c_str());
    }
    return;
  }
  for (int i = 0; i < 4; ++i)
    if (!used[i]) {
      used[i] = 1;
      id[d] = i;
      Choose(d+1);
      used[i] = 0;
    }
}
main() {
  while (scanf("%d %d %d %d %d %d", 
    &s[4].nHP, &s[5].Speed, &s[4].Speed, &HealHP, &HealMP, &ItemMP) == 6 
    && s[4].nHP+s[5].Speed+s[4].Speed+HealHP+HealMP+ItemMP) {
    id[3] = 4, id[4] = 5;
    for (int i = 0; i < 4; ++i) {
      s[(i+3)%4].read();
      used[i] = 0;
    }
    Team.clear();
    for (Limit = 1; Limit < 13; ++Limit) {
      printf("> %d\n", Limit);
      Choose();
      if (Team.size() > 0) break;
    }
    if (Limit >= 13) Limit = -1;
    printf("%d", Limit);
    for (int i = 0; i < Team.size(); ++i)
      printf(" %s", Team[i].c_str());
    puts("");
  }
}
