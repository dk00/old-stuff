#include<cstdio>
int d1[100],d2[100],p[100],c[100][100],c2[100][100];
main()
{
    int i,j,k,n,m,S=1;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i][j]=c[j][i]=k;
        }
        for(k=0;k<n;k++)
        {
            for(i=0;i<n;i++)
                p[i]=1,d1[i]=d2[i]=10000;
            d1[k]=0;
            while(1)
            {
                for(i=0;(!p[i] || d1[i]==10000) && i<n;i++);
                if(i>=n)break;
                for(j=i+1;j<n;j++)
                    if(d1[j]<d1[i] && p[j])i=j;
                p[i]=0;
                for(j=0;j<n;j++)
                {
                    m=d1[i]+c[i][j];
                    if(c[i][j] && m<d1[j])
                    {
                        d2[j]=d1[j];
                        d1[j]=m;
                    }
                    if(c[i][j] && m>d1[j] && m<d2[j])
                        d2[j]=m;
                }
            }
            for(i=0;i<n;i++)p[i]=1;
            while(1)
            {
                for(i=0;(!p[i] || d2[i]==10000) && i<n;i++);
                if(i>=n)break;
                for(j=i+1;j<n;j++)
                    if(d2[j]<d2[i] && p[j])i=j;
                p[i]=0;
                for(j=0;j<n;j++)
                    if(c[i][j] && d2[i]+c[i][j]<d2[j])
                        d2[j]=d2[i]+c[i][j];
            }
            for(i=0;i<n;i++)
                c2[k][i]=d2[i];
        }
        scanf("%d",&k);
        printf("Set #%d\n",S++);
        while(k--)
        {
            scanf("%d %d",&i,&j);
            if(c2[i][j]<10000)
                printf("%d\n",c2[i][j]);
            else
                puts("?");
        }
    }
}
