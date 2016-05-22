#include<cstdio>
const int N=1001;
int n,m,u[N];
char c[N][N];
int go(int d,int v,int t)
{
    int i,j=d+1,k;
    u[v]=d;
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]>=0 && 1-(d-u[i])%2)
            t=d,j<?=u[i];
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]>=0 && u[i]<t)
            j<?=u[i];
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]<0)
        {
            if((k=go(d+1,i,(c[v][i]==2)?d+1:t))<=d)c[v][i]=2;
            j<?=k;
        }
    if(j<=d)m--;
    return j;
}
int main()
{
    int i,j;
    while(scanf("%d %d",&n,&m)>0 && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=i!=j;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1][j-1]=c[j-1][i-1]=0;
        }
        for(i=0;i<n;i++)u[i]=-1;
        for(i=0;i<n;i++)
            if(u[i]<0)go(0,i,0);
        for(i=0;i<n;i++)u[i]=-1;
        for(i=0,m=n;i<n;i++)
            if(u[i]<0)go(0,i,0);
        printf("%d\n",m);
    }
}
