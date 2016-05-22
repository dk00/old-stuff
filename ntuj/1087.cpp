#include<cstdio>
#include<vector>
#include<string>
using namespace std;
char Head[] = "HLMY";
int cHP, cMP, mMP;
struct Char {
  int nHP, HP, nMP, MP, nSP, SP, Spd, Atk, sAtk, sType, cSP, q0, q1;
  int CD, D[2], sD[2];
  void read() {
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
      &HP, &MP, &Spd, &D[0], &sD[0], &D[1], &sD[1], &Atk, &sAtk, &cSP, &sType,
      &q0, &q1, &nHP, &nSP, &nMP);
    CD = 5 - Spd;
  }
  bool ready() {
    if (!--CD) {
      CD = 5 - Spd;
      return true;
    }
    return false;
  }
  bool Cure() {
    if (nMP < cMP) return false;
    nMP -= cMP;
    nHP += cHP;
    if (nHP > HP) nHP = HP;
    return true;
  }
  bool Item() {
    nMP += mMP;
    if (nMP > MP) nMP = MP;
  }
  void Dmg(int i) {
    nSP += q1;
    if (nSP > 100) nSP = 100;
    nHP -= D[i];
  }
  void sDmg(int i) { nHP -= sD[i]; }

} h[4];

struct Field {
  int HP, Spd[2], CD[2], Act[2];
  Char P[3];
  void Attack(int i) {
    P[i].nSP += P[i].q0;
    if (P[i].nSP > 100) P[i].nSP = 100;
    HP -= P[i].Atk;
    P[i].nHP -= P[i].Atk;
  }
  bool Skill(int i) {
    if (P[i].nSP < P[i].cSP) return false;
    HP -= P[i].sAtk;
    if (P[i].sType) P[i].nHP -= P[i].sAtk;
    return true;
  }
} s[99];

int Limit, ID[5];

bool Fight(int d = 0, int turn = 0, int i = 0) {
  for (int k = 0; k < 3; ++k)
    if (s[d].P[k].nHP <= 0) return false;
  if (turn >= Limit) return false;
  if (s[d].HP <= 0) return true;
  int j, k;
  if (i == 4) {
    for (k = 0; k < 2; ++k) {
      Field& F = s[d];
      if (!--F.CD[k]) {
        F.CD[k] = 5 - F.Spd[k];
        j = F.Act[k]++%4;
        if (j == 0)
          for (j = 0; j < 3; ++j)
            F.P[j].sDmg(k);
        else
          F.P[j-1].Dmg(k);
      }
    }
    return Fight(d, turn+1, 0);
  }
  {
    Field& F = s[d+1];    
    if ((j = ID[(i+3)%4]) < 0) return Fight(d, turn, i+1);
    F = s[d];
    Field tmp = s[d];
    if (!s[d].P[j].ready()) return Fight(d, turn, i+1);
    F.Attack(j);
    if (Fight(d+1, turn, i+1)) return true;
    F = tmp;
    if (F.P[j].Cure() && Fight(d+1, turn, i+1)) return true;
    F = tmp;
    F.P[j].Item();
    if (Fight(d+1, turn, i+1)) return true;
    F = tmp;
    return (F.Skill(j) && Fight(d+1, turn, i+1));
  }
}

char used[4], t[4];
vector<string> Team;

bool Choose(int n = 0) {
  if (n >= 3) {
    if (Fight()) {
      t[4] = 0;
      Team.push_back(t);
      return true;
    }
    return false;
  }
  int i;
  bool r = false;
  for (i = 0; i < 4; ++i) {
    if (used[i]) continue;
    used[i] = 1;
    s[0].P[n] = h[i];
    t[n] = Head[i];
    ID[i] = n;
    r |= Choose(n+1);
    ID[i] = -1;
    used[i] = 0;
  }
  return r;
}

main() {
  int i, C = 1;
  while (scanf("%d %d %d %d %d %d", 
    &s[0].HP, &s[0].Spd[0], &s[0].Spd[1], &cHP, &cMP, &mMP) == 6
    && s[0].HP + s[0].Spd[0] + s[0].Spd[1] + cHP + cMP + mMP) {
    s[0].CD[0] = 5 - s[0].Spd[0];
    s[0].CD[1] = 5 - s[0].Spd[1];

    for (i = 0; i < 4; ++i)
      ID[i] = -1, h[(i+3)%4].read();
    for (Limit = 2; Limit <= 12; ++Limit) {
      Team.clear();
      if (Choose()) break;
    }
    if (Limit > 12) Limit = -1;
    printf("Case %d: %d", C++, Limit);
    for (i = 0; i < Team.size(); ++i)
      printf(" %s", Team[i].c_str());
    puts("\n");
  }
}
