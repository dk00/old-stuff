#include<stdio.h>
inline double max(double a,double b)
{
    if(a>b)
        return a;
    return b;
}
double to[100],min[100],d[100][100],r[100][100];
int p[100],q[100],tmp[100];
main()
{
    int i,j,n,m,s,t;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                r[i][j]=d[i][j]=-1;
        scanf("%d %d",&s,&t);
        s--,t--;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            scanf("%lf %lf",&r[i][j],&d[i][j]);
            r[j][i]=r[i][j],d[j][i]=d[i][j];
        }
        for(i=0;i<n;i++)
            p[i]=i,min[i]=-1;
        min[s]=0;
        p[s]=-1;
        for(i=0;i<n;i++)
            if(r[s][i]>0)
                min[i]=r[s][i],p[i]=s;
        while(1)
        {
            for(i=0;(p[i]==i || p[i]<0) && i<n;i++);
            if(i>=n)break;
            for(j=i+1;j<n;j++)
                if(p[j]!=j && p[j]>=0 && min[j]<min[i])
                    i=j;
            p[i]=-1;
            for(j=0;j<n;j++)
                if(r[i][j]>0 && (p[j]==j ||
                max(r[i][j],min[i])<min[j]))
                {
                    p[j]=i;
                    min[j]=max(r[i][j],min[i]);
                }
        }
        for(i=0;i<n;i++)
            p[i]=i,to[i]=-1;
        for(i=0;i<n;i++)
            if(d[s][i]>0)
                p[i]=q[i]=s,to[i]=d[s][i];
        to[s]=0;
        p[s]=-1;
        while(1)
        {
            for(i=0;(p[i]==i || p[i]==-1) && i<n;i++);
            if(i>=n)break;
            for(j=i+1;j<n;j++)
                if(p[j]!=j && p[j]>=0 && to[j]<to[i])
                    i=j;
            p[i]=-1;
            for(j=0;j<n;j++)
                if(d[i][j]>0 && r[i][j]<=min[t] && (p[j]==j ||
                d[i][j]+to[i]<to[j]))
                {
                    p[j]=q[j]=i;
                    to[j]=d[i][j]+to[i];
                }
        }
        for(i=t,j=0;i!=s;i=q[i])
            tmp[j++]=i;
        printf("%d",s+1);
        while(j--)
            printf(" %d",tmp[j]+1);
        printf("\n%.1lf %.1lf\n",min[t],to[t]);
    }
}
