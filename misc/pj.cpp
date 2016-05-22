#include<cmath>
#include<cstdio>
#define EPS 1e-7
const int N=999;
int t,c[N][N],num[N][N],p[N];
double row[N],col[N];
char go(int v)
{
  if(p[v])return 0;
  if(v==t)return 1;
  p[v]=1;
  for(int i=0;i<=t;i++)
    if(c[v][i]-- && go(i))
      return ++c[i][v];
    else c[v][i]++;
  return 0;
}
int flow()
{
  int i,j=0;
  for(i=0;i<=t;i++)p[i]=0;
  while(go(0))
    for(j++,i=0;i<=t;i++)p[i]=0;
  return j;
}
main()
{
  int i,j,n,m,T;
  double k;
  freopen("pj.in","r",stdin);
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d %d",&n,&m);
    t=n+m+1;
    for(i=0;i<=t;i++)
      for(j=0;j<=t;j++)
        c[i][j]=0;
    for(i=1;i<=n;i++)row[i]=0;
    for(j=1;j<=m;j++)col[j]=0;
    for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
      {
        scanf("%lf",&k);
        num[i][j]=(int)floor(k+EPS);
        row[i]+=k-num[i][j];
        col[j]+=k-num[i][j];
        c[i][n+j]=(k-num[i][j]>0.009);
      }
    for(i=1;i<=n;i++)c[0][i]=(int)(row[i]+EPS);
    for(j=1;j<=m;j++)c[n+j][t]=(int)(col[j]+EPS);
    for(i=1,j=0;i<=n;i++)j+=c[0][i];
    if(j!=flow())
    {
      puts("no");
      continue;
    }
    for(i=1;i<=n;i++)
    {
      printf("%d",num[i][1]+c[n+1][i]);
      for(j=2;j<=m;j++)
        printf(" %d",num[i][j]+c[n+j][i]);
      puts("");
    }
  }
}
