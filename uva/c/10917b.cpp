#include<cstdio>
int p[1000],to[1000],num[1000],c[1000][1000];
main()
{
    int i,j,k,n,m;
    while(1)
    {
        scanf("%d %d",&n,&m);
        if(n+m==0)
            break;
        for(i=0;i<n;i++)
        {
            p[i]=i;
            num[i]=0;
            for(j=0;j<n;j++)
                c[i][j]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        p[1]=0,to[1]=0,num[0]=1;
        while(1)
        {
            for(i=0;i<n && (p[i]==i || p[i]==-1);i++);
            if(i>=n)
                break;
            for(j=i+1;j<n;j++)
                if(to[j]<to[i] && p[j]!=j && p[j]!=-1)
                    i=j;
            p[i]=-1;
            for(j=0;j<n;j++)
                if(c[i][j] && (p[j]==j || to[i]+c[i][j]<to[j]))
                    p[j]=i,to[j]=to[i]+c[i][j];
        }
        for(i=0;i<n;i++)
            p[i]=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][j] && to[i]>to[j])
                    p[j]++,c[i][j]=1;
        while(1)
        {
            for(i=0;i<n && p[i]!=0;i++);
            if(i>=n)
                break;
            p[i]=-1;
            for(j=0;j<n;j++)
                if(c[i][j])
                    p[j]--,num[j]+=num[i];
        }
        printf("%d\n",num[1]);
    }
}
