/*
PROB:ppairing
LANG:C++
*/
#include<ctime>
#include<cstdio>
#include<cstdlib>
int n,m,s[100001],a[100001],b[100001];
inline int Rand(){return ((rand()<<15)^rand())%n;}
void choose(int& i,int& j)
{
    while(!s[i=Rand()]);
    while((j=Rand())==i || !s[j]);
}
char go(int d)
{
    int i,j;
    if(d>=m/2)
    {
        while(d--)
            printf("%d %d\n",a[d]+1,b[d]+1);
        return 1;
    }
    for(i=0;i<n;i++)if(s[i]*2>m-d*2)return 0;
    for(i=0;!s[i] && i<n;i++);
    for(j=i++;!s[i] && i<n;i++)
    if(i>=n)return 0;
    while(1)
    {
        choose(i,j);
        s[a[d]=i]--,s[b[d]=j]--;
        if(go(d+1))return 1;
        s[i]++,s[j]++;
    }
}
main()
{
    freopen("ppairing.in","r",stdin);
    freopen("ppairing.out","w",stdout);
    int i;
    srand(time(NULL));
    while(scanf("%d %d",&m,&n)==2)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        go(0);
    }
}
