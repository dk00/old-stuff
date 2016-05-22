/*
PROG: round
LANG: C++
ID: s0000151
*/
#include<cstdio>
int n,k,u[20],p[20],s[20];
int go(int d)
{
    if(d>=n)
        return abs(p[n-1]-p[0])<=k;
    int i,sum=0;
    for(i=1;i<n;i++)
        if(u[i] && abs(p[d-1]-s[i])<=k)
        {
            u[i]--,p[d]=s[i];
            sum+=go(d+1);
            u[i]++;
        }
    return sum;
}
main()
{
    freopen("round.in","r",stdin);
    freopen("round.out","w",stdout);
    int i;
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
        scanf("%d",&s[i]),u[i]=1;
    p[0]=s[0],u[0]=0;
    printf("%d\n",go(1));
    scanf(" ");
}
