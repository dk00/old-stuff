#include<cstdio>
int n,m,w[101],p[101],l[101],s[101][51];
int go(int v)
{
    int i,j,k,sum=0;
    for(j=0;j<=m;j++)
        s[v][j]=-1;
    s[v][0]=0;
    for(i=0;i<=n;i++)
        if(p[i]==v)
        {
            sum+=go(i);
            w[v]+=w[i];
            for(j=m;j>=0;j--)
                for(k=j;k>=0;k--)
                    if(s[i][k]>=0 && s[v][j-k]>=0)
                        s[v][j]>?=s[i][k]+s[v][j-k];
        }

    for(j=m;j>0;j--)
        s[v][j]>?=s[v][j-1]+w[v]*l[v];
    sum+=w[v]*l[v];
    return sum;
}
main()
{
    int i,j;
    p[0]=-1;
    while(scanf("%d %d",&n,&m)==2){
    for(i=1;i<=n;i++)
        scanf("%d %d %d",&w[i],&p[i],&l[i]);
    printf("%d\n",go(0)-s[0][m]);
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=m;j++)
        printf("%4d",s[i][j]);
        puts("");
    }
    }
}
