#include <stdio.h>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main(void)
{
  int a[6][2], i, j, k;
  while(scanf("%d", &a[0][0])!=EOF){
    scanf("%d", &a[0][1]);
    for(i=1;i<6;i++)
      scanf("%d%d", &a[i][0], &a[i][1]);
    map<int, int> r;
    set<int> s;
    for(i=0;i<6;i++) {
      r[a[i][0]]++;
      r[a[i][1]]++;
      s.insert(a[i][0]);
      s.insert(a[i][1]);
    }
    int b[12]={0}, nb=0;
    set<int>::iterator it;
    for(it=s.begin();it!=s.end();it++){
        b[nb++] = *it;
    }
    int f=0;
    for(i=0;i<nb;i++)
      if(r[b[i]]%4!=0)
        f = 1;
    if(nb==3){
      for(i=0;i<3;i++)
        for(j=i+1;j<3;j++){
          int cnt=0;
          for(k=0;k<6;k++)
            if(a[k][0]==b[i] && a[k][1]==b[j] || a[k][0]==b[j] && a[k][1]==b[i])
              ++cnt;
          if(cnt != 2) f = 1;
        }
    }else if(nb==2){
      int d[4]={0}, nd=0;
      for(i=0;i<2;i++)
        for(j=0;j<2;j++){
          int cnt=0;
          for(k=0;k<6;k++)
            if(a[k][0]==b[i] && a[k][1]==b[j] || a[k][0]==b[j] && a[k][1]==b[i])
              ++cnt;
          d[nd++] = cnt;
        }
      sort(d, d+nd);
      if(!(d[0]==0 && d[1]==2 && d[2]==4 && d[3]==4))
        f = 1;
    }
    if(f==1) printf("IMPOSSIBLE\n");
    else printf("POSSIBLE\n");
  }
  return 0;
}
