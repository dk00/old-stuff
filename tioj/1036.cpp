#include<cstdio>
#include<algorithm>
struct pa
{
    int a,b;
    bool operator<(pa x)const{return a<x.a;}
}s[100002];
char notp[5000001];
main()
{
    int i,j,k,l,n,m;
    scanf("%d",&m);
    for(i=0;i<m;i++)
        scanf("%d",&s[i].a),s[i].b=i;
    std::sort(s,s+m);
    s[m].a=2147483647;
    for(j=0;s[j].a<2;j++)
        s[j].a=0;
    while(s[j].a==2)
        s[j++].a=1;
    for(i=3,k=1;i<=s[m-1].a+1;i++)
    {
        while(i>s[j].a)
            s[j++].a=k;
        if(i%2==0 || notp[i/2])continue;
        k++;
        if(i>=46341)continue;
        for(l=i*i;l<=s[m-1].a;l+=i*2)
            notp[l/2]=1;
    }
    for(i=0;i<m;i++)
        std::swap(s[i].a,s[i].b);
    std::sort(s,s+m);
    for(i=0;i<m;i++)
        printf("%d\n",s[i].b);
}
