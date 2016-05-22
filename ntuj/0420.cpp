#include<cstdio>
const int N=1001;
int n,sum,u[N],s[N];
char c[N][N];
int go(int d,int v,int x)
{
    if(u[v]>=0)return (u[v]!=d-2 && (u[v]<=x || (d-u[v])%2))?u[v]:d;
    u[v]=d;
    int i,j=d+1;
    for(i=0;i<n;i++)
        if(c[v][i])
            j<?=go(d+1,i,(s[v] && s[i])?(x>?d):x);
    if(j<=d)
        s[v]=1;
    return j;
}
int main()
{
    int i,j,m,C=1;
    while(scanf("%d %d",&n,&m)>0 && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=1;
        for(i=0;i<n;i++)
            c[i][i]=s[i]=0,u[i]=-1;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1][j-1]=c[j-1][i-1]=0;
        }
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                if(c[i][j])
                    printf("%d %d\n",i+1,j+1);
        for(m=-1,j=0;j>m;)
        {
            for(i=0;i<n;i++)u[i]=-1;
            for(i=0;i<n;i++)
                if(u[i]<0)go(0,i,-1);
            for(m=j,i=j=0;i<n;i++)
                j+=s[i];
        }
        printf("%d\n",n-j);
    }
}
