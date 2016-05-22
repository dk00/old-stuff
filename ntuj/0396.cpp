#include<cstdio>
#include<algorithm>
using namespace std;
int n,t,p[899],to[99],c[99][99],o[99][99];
int go(int v)
{
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=0;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int go()
{
    int i,j,f=0;
    for(;;f++)
    {
        for(i=0;i<=t;i++)p[i]=0;
        if(!go(0))break;
    }
    return f;
}
int res()
{
    int i,j;
    for(i=0;i<=t;i++)
        for(j=0;j<=t;j++)
            c[i][j]=o[i][j];
}
int x1[99],y1[99],x2[99],y2[99];
main()
{
    int i,j,x,y,C=1;
    while(~scanf("%d",&n) && n)
    {
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
        {
            scanf("%d %d %d %d",x1+i,x2+i,y1+i,y2+i);
            if(x1[i]>x2[i])swap(x1[i],x2[i]);
            if(y1[i]>y2[i])swap(y1[i],y2[i]);
            c[0][i+1]=c[i+n+1][t]=1;
        }
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&x,&y);
            for(j=0;j<n;j++)
                if(x1[j]<=x && x<=x2[j] &&  y1[j]<=y && y<=y2[j])
                    c[i+1][j+n+1]=1;
        }
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                o[i][j]=c[i][j];
        printf("Heap %d\n",C++);
        y=0,x=go();
        res();
        for(j=n+1;j<t;j++)
            for(i=1;i<=n;i++)
                if(c[i][j])
                {
                    c[i][j]=0;
                    if(go()<x)
                    {
                        if(y++)putchar(' ');
                        printf("(%c,%d)",'A'+j-n-1,i);
                    }
                    res();
                }
        if(!y)printf("none");
        puts("\n");
    }
}
