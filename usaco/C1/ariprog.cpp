/*
PROB:ariprog
LANG:C++
*/
#include<cstdio>
#include<algorithm>
struct pt
{
    int a,b;
    bool operator<(pt x)const
    {
        if(b!=x.b)return b<x.b;
        return a<x.a;
    }
}r[10000];
char s[125001];
main()
{
    freopen("ariprog.in","r",stdin);
    freopen("ariprog.out","w",stdout);
    int i,j,k,l,n,m;
    
    scanf("%d %d",&m,&n);
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            s[i*i+j*j]=1;
    n=n*n*2;
    register short t=0;
    for(t=0,i=n;i>=m-1;i--)
        if(s[i])for(j=1;j*m-j<=i;j++)
        {
            for(k=i-j*m+j;k<i  && s[k];k+=j);
            if(k==i)r[t++]=(pt){i-j*m+j,j};
        }
    std::sort(r,r+t);
    for(i=0;i<t;i++)
        printf("%d %d\n",r[i].a,r[i].b);
    if(!t)puts("NONE");
    scanf(" ");
}
