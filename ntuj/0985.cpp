#include <stdio.h>
#include <algorithm>
using namespace std;

double p[1005][2];
double d[1005], w[1005];
int srt[1005];
bool cmp(int x,int y){
  return d[x]<d[y];
}
int main(void)
{
  int n, cs=0, i, j;
  double PI = 3.141;
  while(scanf("%d",&n)!=EOF && n>0){
    ++cs;
    double ax, ay, bx, by, T;
    scanf("%lf%lf%lf%lf%lf", &ax,&ay, &bx,&by,&T);
    T /= PI;
    for(i=0;i<n;i++){
      scanf("%lf%lf",&p[i][0],&p[i][1]);
      d[i] = (p[i][0]-ax)*(p[i][0]-ax) + (p[i][1]-ay)*(p[i][1]-ay);
      w[i] = (p[i][0]-bx)*(p[i][0]-bx) + (p[i][1]-by)*(p[i][1]-by);
      srt[i]=i;
    }
    sort(srt, srt+n, cmp);
    int mn = n;
    int cnt=0;
    for(j=0;j<n;j++){
      if(d[j]==0.0 || w[j]<=T) continue;
      ++cnt;
    }
    mn = cnt;
    double S;
    for(i=0;i<n;i++){
      if(d[i]>T) continue;
      S = T - d[i];
      int cnt=0;
      for(j=0;j<n;j++)
        if(d[j]<=d[i] || w[j]<=S) continue;
        else ++cnt;
      if(cnt<mn) mn = cnt;
    }
    printf("%d. %d\n", cs, mn);
  }
  return 0;
}
