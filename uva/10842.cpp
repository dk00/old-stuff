#include<cstdio>
#include<algorithm>
struct E
{
    int s,t,c;
    bool operator<(E x)const{return c<x.c;}
}c[10000];
int s[101],d[101];
int find(int a)
{
    if(s[a]==a)return a;
    return s[a]=find(s[a]);
}
char uni(int a,int b)
{
    a=find(a),b=find(b);
    if(a==b)return 1;
    if(d[a]<d[b])s[a]=b;
    else s[b]=a;
    if(d[a]==d[b])d[a]++;
    return 0;
}
main()
{
    int i,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<m;i++)
            scanf("%d %d %d",&c[i].s,&c[i].t,&c[i].c);
        std::sort(c,c+m);
        for(i=0;i<n;i++)
            s[i]=i,d[i]=0;
        for(i=m-1,n--;n--;)
            while(uni(c[i].s,c[i].t))i--;
        printf("Case #%d: %d\n",C++,c[i].c);
    }
}
