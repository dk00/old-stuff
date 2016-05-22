#include<cstdio>
#include<cstdlib>
int uu,s[100000],t[100000],u[100000];
char go(int x)
{
    if(!x)return 0;
    if(s[x])return s[x]-1;
    int i;
    s[x]=1;
    for(i=1<<30;(x&i)==0;i>>=1);
    for(;s[x]==1 && 1-i%2;i|=i/2)
        if(!go(x^i))s[x]=2,t[x]=x^i;
    if(!go(x^i))s[x]=2;
    return s[x]-1;
}
int count(int x)
{
    if(u[x]==uu)return 0;
    u[x]=uu;
    if(!x)return 1;
    int i,sum=1;
    for(i=1<<30;(x&i)==0;i>>=1);
    for(;1-i%2;i|=i/2)
        sum+=count(x^i);
    sum+=count(x^i);
    return sum;
}
main()
{
    int i;
    char tmp[100];
    for(i=0;i<200;i++)
        if(go(i))
        printf("%d %3d %07s %d\n",go(i),i,itoa(i,tmp,2),t[i]);
    while(scanf("%d",&i))
        uu++,printf("%d\n",count(i));
}
