#include<cstdio>
const long long Inf=2147483647,inf=9223372036854775807ll;
const int V=1200;
char u[V];
int n,p[V],q[V*V],cap[V][V],cost[V][V];
long long d[V+1];
long long sp(){
  int i,j,k;
  for(i=0;i<n;i++)d[i]=inf,u[i]=1;
  q[0]=d[0]=u[0]=0;
  for(i=0,j=1;i<j;i++)
  {
    u[q[i]]=1;
    for(k=0;k<n;k++)
    {
      /*if(cap[q[i]][k]==2 && d[q[i]]-cost[k][q[i]]<d[k]){
        d[k]=d[p[k]=q[i]]-cost[k][q[i]];
        if(u[k])u[q[j++]=k]=0;
      }*/
      if(cap[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k]){
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
  long long tmp,sum=0;
  while((tmp=sp())>=0){
    sum+=tmp;
    for(int i=n-1;i>0;i=p[i])
      cap[p[i]][i]--,cap[i][p[i]]++;
  }
  return sum;
}
int n0,n1,n2,len[V][V],a0[V],b0[V],a1[V],a2[V];
main()
{
  int i,j,k,T,m,sum;
  freopen("pe.in","r",stdin);
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(i!=j)len[i][j]=Inf;
        else len[i][j]=0;
    while(m--)
    {
      scanf("%d %d",&i,&j);
      i--,j--;
      scanf("%d",&k);
      len[i][j]<?=k;
      len[j][i]=len[i][j];
    }
    for(k=0;k<n;k++)
      for(i=0;i<n;i++)
        for(j=0;j<n;j++)
          if(i!=j && len[i][k]<Inf && len[k][j]<Inf)
            len[i][j]<?=len[i][k]+len[k][j];
    sum=0;
    scanf("%d",&n0);
    for(i=0;i<n0;i++)
    {
      scanf("%d %d",a0+i,b0+i);
      a0[i]--,b0[i]--;
      sum+=len[a0[i]][b0[i]];
    }
    scanf("%d",&n1);
    for(i=0;i<n1;i++)
      scanf("%d",a1+i),a1[i]--;
    scanf("%d",&n2);
    for(i=0;i<n2;i++)
      scanf("%d",a2+i),a2[i]--;
    n=n0+n1+2;
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        cap[i][j]=cost[i][j]=0;
    for(i=0;i<n0;i++)
      for(j=0;j<n1;j++)
      {
        int mini=2147483647;
        for(k=0;k<n2;k++)
        {
          mini<?=len[a0[i]][a1[j]]+len[a1[j]][a2[k]]+len[a2[k]][b0[i]];
        }
        cap[i+1][n0+j+1]=1;
        cost[i+1][n0+j+1]=mini-len[a0[i]][b0[i]];
        cost[n0+j+1][i+1]=-cost[i+1][n0+j+1];
      }
    for(i=0;i<n0;i++)cap[0][i+1]=1,cost[0][i+1]=0;
    for(i=0;i<n1;i++)cap[n0+i+1][n-1]=1,cost[n0+i+1][n-1]=0;
    /*for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
        printf("[%3d:%3d]",cap[i][j],cost[i][j]);
      puts("");
    }*/
    i=sum+flow();
    j=(i+n0-1)/n0;
    printf("%02d:%02d\n",8+j/60,j%60);
  }
}

