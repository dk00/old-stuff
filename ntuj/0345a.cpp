#include<cstdio>
const int inf=2147483647;
char c[3001][3001];
int d[3001],q[3001];
main()
{
    int i,j,k,n,m,x,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0,d[i]=inf;j<n;j++)
                c[i][j]=0;
                
        for(i=0;i<m;i++)
        {
            scanf("%d %d",&j,&k);
            j--,k--;
            c[j][k]=c[k][j]=1;
        }
        scanf("%d",&x);
        while(x--)
        {
            scanf("%d %d",&j,&k);
            j--,k--;
            c[j][k]^=1;
            c[k][j]^=1;
        }
        d[q[0]=0]=0;
        for(i=0,j=1;i<j;i++)
            for(k=0;k<n;k++)
                if(c[q[i]][k] && d[q[i]]+1<d[k])
                    d[q[j++]=k]=d[q[i]]+1;
        for(i=j=0;i<n;i++)
            if(d[i]>10 && d[i]<inf)j++;
        printf("%d\n",j);
    }
}
