#include<cstdio>
#include<algorithm>
struct w
{
    char s[5];
    bool operator<(w x)const{return s[1]<x.s[1];}
}s[1001];
main()
{
    char tmp[50];
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%s",s[i].s);
    std::sort(s,s+n);
    scanf("%s",tmp);
    for(i=0;i<n;i++)
        if(s[i].s[0]==tmp[0])
            puts(s[i].s);
}
