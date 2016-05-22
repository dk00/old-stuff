#include<cstdio>
int q[100],p[100],to[100],c[100][10000],r[100][10000],d[100][10000],
    en[100];
inline int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
void printpath(int v)
{
    if(v==-1)
        return ;
    printpath(q[v]);
    printf("%d ",v+1);
}
main()
{
    int i,j,k,n,m,s,t,a,b,min;
    while(scanf("%d %d %d %d",&n,&m,&s,&t)!=EOF)
    {
        s--,t--;
        for(i=0;i<n;i++)
            en[i]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][en[i]]=j;
            c[j][en[j]]=i;
            scanf("%d.%d",&a,&b);
            r[i][en[i]]=a*10+b;
            r[j][en[j]]=a*10+b;
            scanf("%d.%d",&a,&b);
            d[i][en[i]]=a*10+b;
            d[j][en[j]]=a*10+b;
            en[i]++,en[j]++;
        }
        for(i=0;i<n;i++)
            p[i]=i;
        p[s]=-1;
        to[s]=0;
        for(i=0;i<en[s];i++)
        {
            j=c[s][i];
            if(p[j]==j || r[s][i]<to[j])
                to[j]=r[s][i],p[j]=s;
        }
        while(1)
        {
            for(i=0;i<n && (p[i]==i || p[i]==-1);i++);
            if(i>=n)
                break;
            for(j=i+1;j<n;j++)
                if(p[j]!=j && to[j]<to[i] && p[j]!=-1)
                    i=j;
            p[i]=-1;
            for(j=0;j<en[i];j++)
            {
                a=c[i][j];
                if(p[a]==-1)
                    continue;
                b=max(to[i],r[i][j]);
                if(p[a]==a || b<to[a])
                    to[a]=b,p[a]=i;
            }
        }
        min=to[t];
        for(i=0;i<n;i++)
            p[i]=i;
        p[s]=q[s]=-1;
        to[s]=0;
        for(i=0;i<en[s];i++)
        {
            j=c[s][i];
            if(r[s][i]>min)
                continue;
            if(p[j]==j || d[s][i]<to[j])
                to[j]=d[s][i],p[j]=s;
        }
        while(1)
        {
            for(i=0;i<n && (p[i]==-1 || p[i]==i);i++);
            if(i>=n)
                break;
            for(j=i+1;j<n;j++)
                if(p[j]!=j && to[j]<to[i] && p[j]!=-1)
                    i=j;
            q[i]=p[i];
            p[i]=-1;
            for(j=0;j<en[i];j++)
            {
                a=c[i][j];
                if(p[a]==-1 || r[i][j]>min)
                    continue;
                b=to[i]+d[i][j];
                if(p[a]==a || b<to[a])
                    to[a]=b,p[a]=i;
            }
        }
        printpath(q[t]);
        printf("%d\n",t+1);
        printf("%d.%d ",to[t]/10,to[t]%10);
        printf("%d.%d\n",min/10,min%10);
    }
}
