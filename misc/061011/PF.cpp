#include<cstdio>
struct tri  //Russian Doles
{
    int h,d,w;
    void get(){scanf("%d %d %d",&h,&d,&w);}
    void put(){printf("%d %d %d\n",h,d,w);}
    bool fit(tri a)
    {
        return(h-2*w>=a.h && d-2*w>=a.w);
    }
}s[1000];
int p1[1000],p2[1000],d1[1000],d2[1000],c[1000][1000];
main()
{
    int i,j,k,n,n1,n2,first=1;
    while(scanf("%d",&n) && n)
    {
        n*=2;
        for(i=0;i<n;i++)
            d1[i]=d2[i]=0,s[i].get();
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][j]=s[i].fit(s[j]))
                    d1[j]++,d2[j]++;
        for(i=n1=n2=0;i<n;i++)
        {
            for(j=0;j<n && d1[j]>0;j++);
            if(j>=n)break;
            if(n1<n/2 &&(n1==0 || c[p1[n1-1]][j]))
                p1[n1++]=j;
            else
                p2[n2++]=j;
            for(k=0;k<n;k++)
                if(c[j][k])
                    d1[k]--;
            d1[j]=n;
        }
        if(first)first=0;
        else puts("");
        for(i=0;i<n1;i++)
            s[p1[i]].put();
        puts("-");
        for(i=0;i<n2;i++)
            s[p2[i]].put();
    }
}
