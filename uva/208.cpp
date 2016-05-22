#include<cstdio>
const int n=21;
int m;
char c[25][25],tmp[100],u[100],path[100];
bool go(int v)
{
    if(v==m)return 1;
    for(int i=1;i<=n;i++)
        if(c[v][i] && tmp[i])
        {
            tmp[i]=0;
            if(go(i))return 1;
        }
    return 0;
}
int node;
int go(int v,int d)
{
    node++;
    path[d]=v;
    if(v==m)
    {
        for(int i=0;i<d;i++)
            printf("%d ",path[i]);
        printf("%d\n",path[d]);
        return 1;
    }
    for(int i=1;i<=n;i++)tmp[i]=u[i];
    if(!go(v))return 0;
    int i,sum=0;
    for(i=1;i<=n;i++)
        if(c[v][i] && u[i])
        {
            u[i]--;
            sum+=go(i,d+1);
            u[i]++;
        }
    return sum;
}
main()
{
    int i,j,C=1;
    while(scanf("%d",&m)==1)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                c[i][j]=0;
        while(scanf("%d %d",&i,&j) && i+j)
            c[i][j]=c[j][i]=1;
        printf("CASE %d:\n",C++);
        for(i=2;i<=n;i++)u[i]=1;
        node=0;
        printf("There are %d routes from the firestation to streetcorner %d.\n"
        ,go(1,0),m);
    }
}
