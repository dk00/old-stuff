#include<cstdio>
main()
{
    int i,j,k,n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&k,&m);
        n+=k;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
            u[i]=t[i]=-1;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1][j-1]=c[j-1][i-1]=1;
        }
        for(i=0;i<n;i++)
        {
            if(u[i]<0)
                if(go(i))goto no;
            for(j=0;j<n;j++)
                if(t[j]>=0)
                {
                    if(t[j])a[j]++;
                    else b[j]++;
                    t[j]=-1;
                }
        }
        for(i=0;i<n;i++)
            t[i]=0;
        t[0]=1;
        for(j=0;j<n;j++)
        {
            if(a[j]+b[j]==0)continue;
            for(i=n-1;i>0;i--)
            {
                if(a[j] && i>=a[j])t[i]|=t[i-a[j]];
                if(b[j] && i>=b[j])t[i]|=t[i-b[j]];
            }
        }
        if(!t[k])goto no;
        puts("yes");
        continue;
    no: puts("no");
    }
}
