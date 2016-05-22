#include<cstdio>
#include<algorithm>
int t1[1000],t2[1000],s0[131072],*s1=s0+32768,*s2=s0+98304;
struct pt
{
    int x,y;
    bool operator<(pt a)const{return(x<a.x ||(x==a.x && y<a.y));}
}s[1000];
main()
{
    int i,j,n,max;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
        {
            t1[i]=t2[i]=0;
            scanf("%d %d",&s[i].x,&s[i].y);
            if(s[i].y<-32768 || s[i].y>32767)
                s[i].y/=0;
        }
        std::sort(s,s+n);
        std::fill(s0,s0+131072,0);
        for(i=max=0;i<n;i++)
        {
            if(!t1[i])
                for(j=i;j<n && s[i].x==s[j].x;j++)
                    t1[j]=s1[s[j].y]>?1,t2[j]=s2[s[j].y]>?1;
            t1[i]>?=1,t2[i]>?=1;
            max>?=t1[i]>?t2[i];
            if(s[i].y+2<32768)
                s2[s[i].y+2]>?=t1[i]+1;
            if(s[i].y-2>=-32768)
                s1[s[i].y-2]>?=t2[i]+1;
        }
        printf("%d\n",max);
    }
}
