#include<cstdio>
unsigned m,x;
int n,u[10],num[10],p[10];
char check()
{
    int i,j;
    for(i=j=0;(i+p[i])%n;i=(i+p[i])%n,j++);
    return j!=n-1;
}
char go(int d)
{
    if(d>=n)
    {
        if(check())return 0;
        for(d=x=0;d<n;d++)
            x=x*10+p[d];
        if(x>m)return printf("%u\n",x),1;
        return 0;
    }
    for(int i=1;i<=9;i++)
        if((d+i)%n!=d%n && !u[(d+i)%n] && !num[i])
        {
            u[(d+i)%n]--,num[i]--;
            p[d]=i;
            if(go(d+1))return 1;
            u[(d+i)%n]++,num[i]++;
        }
    return 0;
}
main()
{
    freopen("runround.in","r",stdin);
    freopen("runround.out","w",stdout);
    int i;
    scanf("%u",&m);
    for(i=1,n=0;i<=m;i*=10,n++);
    if(!go(0))n++,go(0);
    scanf(" ");
}
/*
PROB:runround
LANG:C++
*/
