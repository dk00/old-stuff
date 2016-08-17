#include<cstdio>
#include<algorithm>
struct pt
{
    int x,y;
    bool operator<(pt a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
}s[2000001];
char notp[2000001];
int p[350000];
main()
{
    int i,j,n,C=1;
    for(i=1;i<=2000000;i++)
        s[i-1].x=1,s[i-1].y=i;
    p[0]=2;
    for(i=3,n=1;i<=2000000;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j>=0 && j<=2000000;j+=i*2)
            notp[j]=1;
        p[n++]=i;
    }
    for(i=1;i<=2000000;i++)
        for(j=0;(i+1)*p[j]-1<=2000000;j++)
            s[(i+1)*p[j]-1].x=s[i].x+1;
    std::sort(s,s+2000000);
    while(scanf("%d",&i)==1 && i)
        printf("Case %d: %d\n",C++,s[i-1].y);
}
