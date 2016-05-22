#include<cstdio>
const int N=500,M=500,L=2;
int n,m,t,u[N][M][2],c[M][M],ut[M][M*2],to[M];
char check(int d)
{
    int i,j,k;
    for(i=1;i<=d;i++)
    {
        k=to[i];
        for(j=1;j<=m;j++)
            if(i!=j && !c[i][j])k--;
        if(k<0)return 1;
    }
    return 0;
}
int go(int d,int i,int x)
{
    int j;
    if(d>m)return 1;
    //if(check(d))return 0;
    if(i>=n)return go(d+1,0,x);
    for(j=0;j<t;j++)
    {
        if(!ut[d][j])continue;
        ut[d][j]--;
        if(!u[i][j][0] && x)
        {
            u[i][j][0]=d;
            if(go(d,i+1,x-1))return 1;
            u[i][j][0]=0;
        }
        if(u[i][j][0] && u[i][j][0]<d && !u[i][j][1] && c[u[i][j][0]][d]<L)
        {
            to[u[i][j][0]]--;
            to[d]--;
            c[u[i][j][0]][d]++;
            c[d][u[i][j][0]]++;
            u[i][j][1]=d;
            if(go(d,i+1,x))return 1;
            u[i][j][1]=0;
            c[u[i][j][0]][d]--;
            c[d][u[i][j][0]]--;
            to[u[i][j][0]]++;
            to[d]++;
        }
        ut[d][j]++;
    }
    return 0;
}
main()
{
    int i,j;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<=m;j++)
                u[i][j][0]=u[i][j][1]=0;
        for(i=0;i<n;i++)
            u[i][i][0]=1;
        for(i=1;i<=m;i++)
            for(j=1;j<=m;j++)
                c[i][j]=0;
        t=m+1;
        for(i=2;i<=m;i++)
            for(j=0;j<=t;j++)
                ut[i][j]=1;
        for(i=1;i<=m;i++)
            to[i]=n;
        printf("%d\n",go(2,0,n*m/2-n));
        for(i=0;i<n;i++)
        {
            for(j=0;j<t;j++)
            {
                if(u[i][j][0])
                    printf(" %d-%d",u[i][j][0],u[i][j][1]);
                else
                    printf(" ---");
            }
            puts("");
        }
    }
}
