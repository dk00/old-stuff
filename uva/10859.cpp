#include<cstdio>
const int max=2007;
int s1[max],s2[max],t1[max],t2[max],d[max],c[max];
bool go(int v)
{
    if(s1[v]>=0)return 1;
    s1[v]=t1[v]=0;
    s2[v]=1,t2[v]=0;
    for(int i=d[v];i<d[v+1];i++)
    {
        if(go(c[i]))continue;
        s1[v]+=s2[c[i]],t1[v]+=t2[c[i]];
        if(s2[c[i]]<=s1[c[i]] && t2[c[i]]+1>=t1[c[i]])
            s2[v]+=s2[c[i]],t2[v]+=t2[c[i]]+1;
        else
            s2[v]+=s1[c[i]],t2[v]+=t1[c[i]];
    }
    return 0;
}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        /*for(i=0;i<max;i++)
            s1[i]=s2[i]=t1[i]=t2[i]=d[i]=c[i]=0;*/
        scanf("%d %d",&n,&m);
        for(i=0;i<=n;i++)s1[i]=d[i]=0;
        for(i=0;i<m;i++)
        {
            scanf("%d %d",&t1[i],&t2[i]);
            d[t1[i]+1]++,d[t2[i]+1]++;
        }
        for(i=1;i<=n;i++)
            d[i]+=d[i-1];
        for(i=0;i<m;i++)
            c[d[t1[i]]+s1[t1[i]]++]=t2[i];
        for(i=0;i<n;i++)s1[i]=-1;
        for(i=j=k=0;i<n;i++)
            if(s1[i]<0)
            {
                go(i);
                if(s1[i]<s2[i] ||(s1[i]<=s2[i] && t1[i]>=t2[i]))
                    j+=s1[i],k+=t1[i];
                else
                    j+=s2[i],k+=t2[i];
            }
        printf("%d %d %d\n",j,k,m-k);
    }
}
