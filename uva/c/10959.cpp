#include<cstdio>
int c[1000][1000],q[1000],d[1000];
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        for(i=0;i<n;i++)
            d[i]=10000;
        d[0]=q[0]=0;
        for(i=0,j=1;i<j;i++)
            for(k=0;k<n;k++)
                if(c[q[i]][k] && d[q[i]]+1<d[k])
                    q[j++]=k,d[k]=d[q[i]]+1;
        for(i=1;i<n;i++)
            printf("%d\n",d[i]);
        if(T)puts("");
    }
}
