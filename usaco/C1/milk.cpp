/*
PROB:milk
LANG:C++
*/
#include<cstdio>
#include<algorithm>
struct milk
{
    int p,a;
    bool operator<(milk x)const{return p<x.p;}
}s[5000];
main()
{
    int i,n,m;
    freopen("milk.in","r",stdin);
    freopen("milk.out","w",stdout);
    scanf("%d %d",&m,&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&s[i].p,&s[i].a);
    std::sort(s,s+n);
    for(i=n=0;m>0;i++)
        n+=s[i].p*(m<?s[i].a),m=(m-s[i].a)>?0;
    printf("%d\n",n);
}
