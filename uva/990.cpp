#include<cstdio>
int w,s[2006],s1[50][2007],p[2006];
void go(int v,int d)
{
    if(v==0)
    {
        printf("%d\n",d);
        return;
    }
    go(p[v],d+1);
    printf("%d %d\n",(v-p[v])/3/w,s[v]-s[p[v]]);
}
main()
{
    int i,d,v,t,n,C=0;
    while(scanf("%d %d",&t,&w)==2)
    {
        for(i=1;i<=t;i++)s[i]=-1,p[i]=-1;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&d,&v);
            d*=3*w;
            for(i=t-d;i>=0;i--)
                if(s[i]>=0 && s[i]+v>s[i+d])
                    s[i+d]=s[i]+v,p[i+d]=i;
        }
        for(i=v=0;i<=t;i++)
            if(s[i]>s[v])v=i;
        if(!C++)puts("");
        printf("%d\n",s[v]);
        go(v,0);
    }
}
