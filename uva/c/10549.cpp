#include<cstdio>
#include<algorithm>
struct doll
{
    int h,d,w;
    bool operator<(doll a)const{return h<a.h;}
    bool fit(doll a)
    {
        return(h-2*w>=a.h && d-2*w>=a.d);
    }
}s[1000];
int n,n1,n2,p1[1000],p2[1000];
int snum;
inline bool go(int d)
{
    snum++;
    if(d>=n*2)return 1;
    if(n1<=n && s[d].fit(s[p1[n1-1]]))
    {
        p1[n1++]=d;
        if(go(d+1))return 1;
        n1--;
    }
    if(n2<=n && s[d].fit(s[p2[n2-1]]))
    {
        p2[n2++]=d;
        if(go(d+1))return 1;
        n2--;
    }
    return 0;
}
main()
{
    int i;
    s[999]=(doll){-1,-1,0};
    p1[0]=p2[0]=999;
    while(scanf("%d",&n) && n)
    {
        for(i=snum=0;i<n*2;i++)
            scanf("%d %d %d",&s[i].h,&s[i].d,&s[i].w);
        std::sort(s,s+n*2);
        n1=n2=1;
        go(0);
        for(i=n;i>0;i--)
            printf("%d %d %d\n",s[p1[i]].h,s[p1[i]].d,s[p1[i]].w);
        puts("-");
        for(i=n;i>0;i--)
            printf("%d %d %d\n",s[p2[i]].h,s[p2[i]].d,s[p2[i]].w);
        //printf("%d\n",snum);//puts("");
    }
}
