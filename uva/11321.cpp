#include<cstdio>
#include<algorithm>
int n,m,s[10001];
bool cmp(int a,int b)
{
    if(a%m!=b%m)
        return a%m<b%m;
    if(abs(a)%2!=abs(b)%2)
        return abs(a)%2>abs(b)%2;
    if(a%2)
        return a>b;
    return a<b;
}
main()
{
    int i;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        printf("%d %d\n",n,m);
        std::sort(s,s+n,cmp);
        for(i=0;i<n;i++)
            printf("%d\n",s[i]);
    }
}
