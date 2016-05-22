#include<cstdio>
#include<algorithm>
int m,num[10000],p[10000],d[10000],s[5000],t[5000];
char c[10000],r[5000][100];
int look(int v)
{
    int i,j,k;
    for(i=0,j=m-1;i<=j;)
    {
        k=(i+j)/2;
        if(num[k]>v)j=k-1;
        else if(num[k]<v)i=k+1;
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
void rev(int v)
{
    for(int i=0;i<m;i++)
        if(find(i)==v)c[i]^=1;
}
main()
{
    int i,j,k,n;
    while(scanf("%d",&n) && n!=-1)
    {
        scanf("%d",&n);
        for(i=j=0;i<n;i++)
        {
            scanf("%d %d %s",s+i,t+i,r+i);
            t[i]++,r[i][0]=(r[i][0]=='o');
            num[j++]=s[i],num[j++]=t[i];
        }
        std::sort(num,num+j);
        for(i=m=1;i<j;i++)
            if(num[i]!=num[i-1])
                num[m++]=num[i];
        for(i=0;i<m;i++)
            p[i]=i,d[i]=c[i]=0;
        for(i=0;i<n;i++)
        {
            s[i]=look(s[i]),t[i]=look(t[i]);
            j=find(s[i]),k=find(t[i]);
            if(j==k)
            {
                if(r[i][0]^(c[s[i]]!=c[t[i]]))break;
                else continue;
            }
            if(c[s[i]]^c[t[i]]^r[i][0])
                rev(j);
            uni(j,k);
        }
        printf("%d\n",i);
    }
}
