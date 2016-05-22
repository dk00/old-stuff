#include<cstdio>
#include<algorithm>
int m,p[10000],h[10000],d[10000],s[5000],t[5000];
char r[5000][5];
int look(int v)
{
    int i,j,k;
    for(i=0,j=m-1;i<=j;)
    {
        k=(i+j)/2;
        if(h[k]>v)j=k-1;
        else if(h[k]<v)i=k+1;
        else return k;
    }
}
int find(int v)
{
    if(p[v]==v)return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
char check(int n)
{
    for(int i=0;i<n;i++)
        if(r[i][0] && find(h[s[i]])==find(h[t[i]]))
            return 1;
    return 0;
}
main()
{
    int i,j,n;
    while(scanf("%d",&n) && n>=0)
    {
        scanf("%d",&n);
        for(i=j=0;i<n;i++)
        {
            scanf("%d %d %s",s+i,t+i,r+i);
            t[i]++,r[i][0]=(r[i][0]=='o');
            h[j++]=s[i];
            h[j++]=t[i];
        }
        std::sort(h,h+j);
        for(i=m=1;i<j;i++)
            if(h[i]!=h[i-1])
                h[m++]=h[i];
        for(i=0;i<n;i++)
            s[i]=look(s[i]),
            t[i]=look(t[i]);
        for(i=0;i<m;i++)
            p[i]=i,d[i]=0,h[i]=-1;
        for(i=m=0;i<n;i++)
        {
            if(h[s[i]]==-1)
                h[s[i]]=m++;
            h[s[i]]=find(h[s[i]]);
            if(r[i][0])
            {
                if(h[t[i]]==-1)
                    h[t[i]]=m++;
                h[t[i]]=find(h[t[i]]);
                if(h[s[i]]==h[t[i]])break;
            }
            else
            {
                if(h[t[i]]==-1)
                {
                    h[t[i]]=h[s[i]];
                    continue;
                }
                h[t[i]]=find(h[t[i]]);
                uni(h[s[i]],h[t[i]]);
                if(check(i))break;
            }
        }
        printf("%d\n",i);
    }
}
