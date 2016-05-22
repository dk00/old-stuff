#include<cmath>
#include<cstdio>
#define EPS 1e-7
const int V=555,N=555;
char u[V];
int n,p[V],q[V*V],c[V][V];
double inf=10e10,cost[V][V],d[V+1];
double sp(){
  int i,j,k;
  for(i=0;i<n;i++)d[i]=inf,u[i]=1;
  d[0]=q[0]=u[0]=0;
  for(i=0,j=1;i<j;i++)
  {
    u[q[i]]=1;
    for(k=0;k<n;k++)
    {
      if(c[q[i]][k]==2 && d[q[i]]-cost[k][q[i]]<d[k])
      {
        d[k]=d[p[k]=q[i]]-cost[k][q[i]];
        if(u[k])u[q[j++]=k]=0;
      }
      if(c[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k]){
        d[k]=d[p[k]=q[i]]+cost[q[i]][k];
        if(u[k])u[q[j++]=k]=0;
      }
    }
  } 
  if(d[n-1]<inf)return d[n-1];
  return -1;
}
long long flow()
{ 
  long long x=0;
  double sum=0,tmp;
  while((tmp=sp())>=0){
    sum+=tmp,x++;
    for(int i=n-1;i>0;i=p[i])
      c[p[i]][i]--,c[i][p[i]]++;
  }
  return x;
}
double row[N],col[N];
int num[N][N];
main()
{
  int i,j,x,m,T;
  double k;
  freopen("pj.in","r",stdin);
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d %d",&n,&m);
    int t=n+m+1;
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
        cost[i][n+j]=1-k+num[i][j];
        row[i]+=k-num[i][j];
        col[j]+=k-num[i][j];
        c[i][n+j]=(k-num[i][j]>0.009);
      }
    for(i=1;i<=n;i++)cost[0][i]=0,c[0][i]=(int)(row[i]+EPS);
    for(j=1;j<=m;j++)cost[n+j][t]=0,c[n+j][t]=(int)(col[j]+EPS);
    for(i=1,j=0;i<=n;i++)j+=c[0][i];
    x=n,n=t+1;
    if(j!=flow())
    {
      puts("no");
      continue;
    }
    /*for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
        printf("[%2d:%2.2lf]",c[i][j],cost[i][j]);
      puts("");
    }*/
    for(i=1;i<=x;i++)
    {
      printf("%d",num[i][1]+c[x+1][i]);
      for(j=2;j<=m;j++)
        printf(" %d",num[i][j]+c[x+j][i]);
      puts("");
    }
  }
}
