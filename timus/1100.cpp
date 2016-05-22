#include<cstdio>
#include<algorithm>
struct pa
{
    int u,c;
    bool operator<(pa x)const{return c>x.c;}
}s[150000];
main()
{
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&s[i].u,&s[i].c);
    std::stable_sort(s,s+n);
    for(i=0;i<n;i++)
        printf("%d %d\n",s[i].u,s[i].c);
}
