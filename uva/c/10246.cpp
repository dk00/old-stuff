#include<cstdio>
int s[100],a[100][100],c[100][100];
int min(int a,int b){return a<?b;}
int max(int a,int b){return a>?b;}
main()
{
    int i,j,k,n,m,q;
    while(scanf("%d %d %d",&n,&m,&q) && n+m+q)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d",&s[i]);
            for(j=0;j<n;j++)
                a[i][j]=c[i][j]=100000000;
            c[i][i]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]=min(c[i][j],c[i][k]+c[k][j]);
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    a[i][j]=min(a[i][j],c[i][k]+c[k][j]+s[k]);
        while(q--)
        {
            scanf("%d %d",&i,&j);
            if(a[--i][--j]<0)
                puts("-1");
            else
                printf("%d\n",c[i][j]);
        }
    }
}
