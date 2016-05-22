#include<cstdio>
main()
{
    while(scnaf("%d",&n) && n>=0)
    {
        scanf("%d %d",&t,&m);
        t--;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        for(i=0;i<n;i++)p[i]=i;
        p[t]=-t,d[t]=0;
        for(k=1;k<n;k++)
        {
            for(i=0;p[i]>=0;i++);
            for(j=i+1;j<n;j++)
                if(p[j]<0 && d[j]<d[i])i=j;
            p[i]*=-1;
            for(j=0;j<n;j++)
                if(p[i]==i || d[i]+c[i][j]<d[j])
                    d[j]=d[i]+c[i][j],p[j]=-i;
        }
        scanf("%d",&m);
        for(i=0;i<m;i++)
        {
            scanf("%d",x+i);
            
        }
    }
}
