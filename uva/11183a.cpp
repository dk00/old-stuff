#include<cstdio>
struct E{int s,t,c,o;}c[50000];
int p[1001],d[1001],to[1001],oct[1001],pre[1001],help[1001],u[50000];
int find(int v)
{
    if(p[v]==v)return v;
    return(p[v]=find(p[v]));
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
void go(int v)
{
    if(!oct[v])return;
    oct[v]=0;
    go(pre[v]);
}
main()
{
    int i,j,k,n,m,sum,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)p[i]=i,d[i]=0;
        for(i=0;i<m;i++)
        {
            u[i]=1;
            scanf("%d %d %d",&c[i].s,&c[i].t,&c[i].o);
            c[i].c=c[i].o;
        }
        k=sum=0;
        while(m>0)
        {
            for(i=1;i<n;i++)
            {
                if(p[i]==i)to[i]=help[i]=-1;
                oct[i]=1;
            }
            for(i=0;i<m;i++)
                if(c[i].t!=k && p[c[i].t]==c[i].t
                 &&(to[c[i].t]<0 || c[i].c<c[to[c[i].t]].c))
                    to[c[i].t]=i;
            for(i=1;k>=0 && i<n;i++)
                if(p[i]==i)
                {
                    if(to[i]<0){k=-1;break;}
                    sum+=c[to[i]].c,pre[c[to[i]].t]=c[to[i]].s;
                    help[c[to[i]].t]=c[to[i]].c;
                }
            if(k<0)break;
            for(i=0;i<m;i++)
                if(help[c[i].t]>=0)
                    c[i].c=c[i].c-help[c[i].t];
            for(i=1;i<n;i++)
                if(to[i]>=0)
                {
                    if(find(pre[i])==find(i))go(i);
                    else uni(pre[i],i);
                    to[i]=-1;
                }
            k=find(k);
            for(i=0;i<n;i++)
                if(find(i)==k)oct[i]=0;
            for(i=0;i<m;i++)
                if(find(c[i].s)==find(c[i].t) || find(c[i].t)==k
                || oct[c[i].t])u[i]=0;
            for(i=j=0;i<m;i++)
                if(u[i])
                {
                    c[j]=c[i];
                    c[j].s=find(c[j].s);
                    c[j].t=find(c[j].t);
                    u[j++]=1;
                }
            m=j;
        }
        printf("Case #%d: ",C++);
        for(i=0;i<n;i++)
            if(find(i)!=k)k=-1;
        if(k<0)puts("Possums!");
        else printf("%d\n",sum);
    }
}


