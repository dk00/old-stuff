#include<cstdio>
int n,t,v[150],p[150],q[150],to[150],c[150][150];
int go(int p)
{
    if(v[p])
        return 0;
    v[p]=1;
    int sum=1;
    for(int i=0;i<n;i++)
        if(c[p][i])
            sum+=go(i);
    return sum;
}
int path(int u,int f)
{

}
int flow(int max)
{
    int i,j,k,f=0;
    while(1)
    {
        for(i=0;i<n;i++)
            v[i]=-1;
        v[0]=0,q[0]=0;
        for(i=0,j=1;i<j;i++)
            for(k=0;k<n;k++)
                if(c[q[i]][k] && v[k]<0)
                {
                    p[k]=q[i],v[k]=v[q[i]]+1,q[j++]=k;
                    to[k]=(c[q[i]][k]<?to[i]);
                }
        if(v[t]<0)
            return f;
        for(i=1;i<n && f<min;i++)
            if(c[i][t] && v[i]>0)
                f+=path(t,(to[i]<?c[i][t]));
        if(f>=min)
            return min;
    }
}
main()
{
    int i,j,k,m,t,C=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(v[i]=p[i]=j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i-1][j-1]=c[j-1][i-1]=k;
            p[i-1]+=k,p[j-1]+=k;
        }
        printf("Case #%d: ",C++);
        if(go(0)<n)
        {
            puts("0");
            continue;
        }
        for(i=t=0;i<n;i++)
            if(p[t]<p[i])t=i;
        min=flow(150000);
        for(t=1;t<n;t++)
        {
            k=flow(min);
            if(k<min)min=k;
        }
        printf("%d\n",min);
    }
}
