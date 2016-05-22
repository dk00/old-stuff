#include<cstdio>
const int N=1001,inf=2147483647;
long long s[N];
int m,c[N],p[N],t[N];
long long cost(int a,int b)
{
  long long x=c[b]-c[a];
  return (x-100)*(x-100);
}
void print(int v)
{
  if(v)print(p[v]);
  t[m++]=v;
}
main()
{
  int i,j,n;
  long long k;
  freopen("pc.in","r",stdin);
  while(scanf("%d",&n)>0 && n)
  {
    for(i=1;i<=n;i++)
    {
      scanf("%d",c+i);
      c[i]+=c[i-1];
      s[i]=inf;
    }
    s[0]=0;
    for(i=1;i<=n;i++)
      for(j=0;j<i;j++)
      {
        k=s[j]+cost(j,i);
        if(k<s[i])
          s[i]=k,p[i]=j;
      }
    printf("p=%I64d\n",s[n]);
    m=0,print(n);
    for(i=0;i<m;i++)
    {
      printf(" %d",t[i]);
      if(i%30==29)puts("");
    }
    if(m%30)puts("");
    puts("");
  }
}
        /*tmp0[0]=tmp1[0]=0;
        scanf("[0123456789] %[.0123456789]",tmp0,tmp1);
        num[i][j]=0;
        sscanf(tmp0,"%d",&num[i][j]);
        if(tmp1[0]=='.')
        {
          sscanf(tmp1,"%d",&k);
          
          c[i][j]=!!k;
        }*/
