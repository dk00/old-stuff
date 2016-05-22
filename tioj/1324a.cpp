#include<cstdio>
struct sint //3 5 4 3 1234
{
    int n,m,k;
    sint(int a=0):n(a){}
    void operator*=(sint a)
    {
        long long tmp=1ll*n*a.n;
        if(tmp>k)n=k+(tmp-k)%m;
        else n=tmp;
    }
    bool operator==(sint a){return n==a.n;}
}s[100000];
int pow(int n,int k,int m)
{
    if(!k)return 1;
    if(k%2)return 1ll*n*pow(n,k-1,m)%m;
    n=pow(n,k/2,m);
    return n*1ll*n%m;
}
int n,u[1000000],v[1000000];
int get(int x,int m)
{
    int i,j,y,z,st;
    static int u0=0;
    u0++;
    st=pow(x,m,m);
    for(i=0,y=st;i*i<m;i++)
    {
        if(v[y=y*1ll*x%m]==u0)
            return i;
        v[y]=u0;
    }
    z=pow(x,i,m);
    for(j=i*2;v[y=y*1ll*z%m]!=u0;j+=i)
        {i++;i--;}
    for(z=st;(z=z*1ll*x%m)!=y;j--);
    return j-1;
}
int get(int x,int n,int m)
{
    int i,j,k,a=1,y,z;
    z=pow(x,n,m);
    for(i=1,j=10000000;i<=j;)
    {
        k=(i+j)/2;
        y=pow(x,k,m);
        if(y*1ll*z%m==y)
            a=k,j=k-1;
        else
            i=k+1;
    }
    return a;
}
int go(int d)
{
    if(d>=n)return 1;
    int i,j;
    sint x=s[d];
    x.n=1,x*=s[d];
    for(j=0;j<=x.k+x.m;j++)u[j]=-1;
    for(i=1;;i++)
    {
        if(u[x.n]>=0)break;
        u[x.n]=i;
        x*=s[d];
    }//1394 7 12 43 230 374 422 920 785*/
    s[d+1].m=get(s[d].n,s[d].m);
    s[d+1].k=get(s[d].n,s[d+1].m,s[d].m);
    /*if(u[x.n]!=s[d+1].k && s[d+1].k==1 && u[x.n]>1)
        printf("%d %d %d\n",s[d].n/0,s[d+1].m,s[d].m);*/
    s[d+1].k=u[x.n];
    s[d+1].m=i-u[x.n];
   // printf("%d %d\n",s[d+1].k,s[d+1].m);
    j=go(d+1);
    if(s[d].n==328)
    {
        j++,j--;
    }
  //  printf("%d\n",j);
    for(x.n=1,i=0;i<j;i++,x*=s[d])
        if(x.n>x.k)break;
    if(i<j)
    {
        return s[d].k+(pow(s[d].n,j,s[d].m)+s[d].m-s[d].k%s[d].m)%s[d].m;
    }
    return x.n;
}
main()
{
    int i,C=1;
    while(scanf("%d",&n)==1 && n)
    {
        s[0].k=0;
        for(i=0;i<n;i++)
            scanf("%d",&s[i].n);
        scanf("%d",&s[0].m);
        printf("%d\n",go(0));
    }
}
