#include<stdio.h>
const int inf=2000000001;
int n,m,w[101],p[101],l[101],path[101],s[101][51];
int calc(int v)
{
    int i,sum=0;
    for(i=0;i<=n;i++)
        if(p[i]==v)
        {
            l[i]+=l[v];
            sum+=calc(i);
            w[v]+=w[i];
        }
    return sum+w[v]*(l[v]-l[p[v]]);
}
int d=0;
int go(int v)
{
    int i,j;
    path[d++]=v;
    for(j=m;j>0;j--)
        for(i=d-2;i>=0;i--)
        {
            int tmp=(l[v]-l[i])*w[v];
            if(s[path[i]][j-1]<inf && s[v][j]>s[path[i]][j-1]-tmp)
                s[v][j]=s[path[i]][j-1]-tmp;
        }
    for(i=0;i<=n;i++)
        if(p[i]==v)
        {
            go(i);
            for(j=0;j<=m;j++)
                if(s[v][j]>s[i][j])
                    s[v][j]=s[i][j];
        }
    return s[v][m];
    d--;
}
main()
{
    int i,j;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d %d %d",&w[i],&p[i],&l[i]);
    p[0]=-1;
    for(i=0;i<=n;i++)
        for(j=0;j<=m;j++)
            s[i][j]=inf;
    s[0][0]=0;
    printf("%d\n",calc(0)+go(0));
}
