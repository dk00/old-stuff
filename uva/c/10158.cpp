#include<cstdio>
short n,p[10000],d[10000],num[10000],top[10000],ne[10000];
char c[10000];
inline int find(int v)
{
    if(p[v]==v)return v;
    return p[v]=find(p[v]);
}
inline void change(int i)
{
    int x=top[i];
    for(;x!=i;i=ne[i])
        c[i]^=1;
    c[i]^=1;
}
inline void uni(int a,int b)
{
    if(d[a]<d[b])
    {
        p[a]=b,num[b]+=num[a];
        ne[top[b]]=a;
        top[b]=top[a];
    }
    else
    {
        p[b]=a,num[a]+=num[b];
        ne[top[a]]=b;
        top[a]=top[b];
    }
    if(d[a]==d[b])d[a]++;
}
main()
{
    int i,j,k,p1,q1;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            p[i]=top[i]=i,num[i]=1,d[i]=0;
        while(scanf("%d %d %d",&i,&j,&k) && i+j+k)
        {
            p1=find(j),q1=find(k);
            if(i<3)
            {
                i--;
                if(p1!=q1)
                {
                    if(c[j]^c[k]^i)
                    {
                        if(num[p1]<num[q1])change(p1);
                        else change(q1);
                    }
                    uni(p1,q1);
                }
                else if(c[j]^c[k]^i)
                    puts("-1");
            }
            else
            {
                i-=3;
                if(p1==q1)
                    printf("%d\n",1^c[j]^c[k]^i);
                else
                    puts("0");
            }
        }
    }
}
