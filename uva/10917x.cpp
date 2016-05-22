#include<cstdio>
int p[1001],to[1001],num[1001],c[1001][1001];
main()
{
    int i,j,k,n,m;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        scanf("%d",&m);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        for(i=0;i<n;i++)
            p[i]=i;
        p[1]=0,to[1]=0;
        while(1)
        {
            for(i=0;(p[i]==i || p[i]==-1) && i<n;i++);
            if(i>=n)
                break;
            for(j=i+1;j<n;j++)
                if(to[j]<to[i] && p[j]!=j && p[j]!=-1)
                    i=j;
            p[i]=-1;
            for(j=0;j<n;j++)
                if(p[j]!=-1&&c[i][j]&&(p[j]==j||to[i]+c[i][j]<to[j]))
                    p[j]=i,to[j]=to[i]+c[i][j];
        }
        for(i=0;i<n;i++)
            p[i]=num[i]=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(c[i][j] && to[i]>to[j])
                    c[i][j]=1,p[j]++;
                else
                    c[i][j]=0;
            }
        num[0]=1;
        while(1)
        {
            for(i=0;i<n && p[i]>0;i++);
            if(i>=n)
                break;
            for(j=0;j<n;j++)
                if(c[i][j])
                    p[j]--,num[j]+=num[i];
            p[i]=2147483647;
        }
        printf("%d\n",num[1]);
    }
}
