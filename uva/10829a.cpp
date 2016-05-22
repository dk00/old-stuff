#include<cstdio>
const int maxn=50005;
#include"suffixarray.h"
int s[maxn],t[maxn],d[maxn],x[maxn],ml[17][maxn],mr[17][maxn],ub[65536];
void go(int s[],int t[],int d[],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)x[t[i]]=i;
    for(i=j=0;i<n;i++)
    {
        if(x[i]==n-1)
        {j=d[i]=0;continue;}
        k=t[x[i]+1];
        while(s[i+j]==s[k+j])
            j++;
        d[x[i]]=j;
        j-=(j>0);
    }
}
void prermq(int z[],int ml[17][maxn],int mr[17][maxn],int n)
{
    int i,j,k,p;
    for(i=1,p=1;i<=n;i*=2,p++)
        for(j=0;j<n;j+=i)
        {
            ml[p][j]=z[j];
            for(k=j+1;k<=j+i;k++)
                ml[p][k]=(z[k]<?ml[p][k-1]);
            mr[p][j+i-1]=z[j+i-1];
            for(k=j+i-1;k>=j;k--)
                mr[p][k]=(z[k]<?mr[p][k+1]);
        }
}
char tmp[maxn];
int lcp(int i,int j)
{
    i=x[i],j=x[j];
    if(i>j)i^=j^=i^=j;
    int k=ub[i^j];
    return (mr[k][i])<?(ml[k][j]);
}
int find(int v,int l1,int l2)
{
    if(!lcp(v-l1+1,v))return v;
    int i,j,k,last=lcp(v-l1,v);
    for(i=0,j=l2-1;i<=j;)
    {
        k=(i+j)/2;
        if(lcp(v-l1-k,v-k)!=last+k)j=k-1;
        if(k<l2-1 && lcp(v-l1-k-1,v-k-1)==last+k+1)i=k+1;
        else break;
    }
    if(lcp(v-l1+1-k,v-k)<l2)
        return v;
    return v-k;
}
main()
{
    int i,j,k,l,n,g,T,C=1;
    for(i=1,k=0;i<32768;i*=2,k++)
        for(j=i*2-1;j>=i;j--)ub[j]=k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %s",&g,tmp);
        for(n=0;tmp[n];n++)
            s[n]=tmp[n]-'a'+1;
        s[n]=s[n+1]=s[n+2]=0;
        suffixArray(s,t,n,26);
        go(s,t,d,n);
        for(i=0;i<n;i++)
            printf("%2d %s\n",t[i],tmp+t[i]);
        prermq(d,ml,mr,n);
        for(i=1+g,k=0;i<n;i++)
            for(j=i;j<n;j+=i-g)
            {
                j=find(j,i,i-g);
                l=lcp(j-i,j);
                if(l+g>=i)k+=l+g-i+1;
                if(l>0)j+=l-1;
            }
        printf("Case %d: %d\n",C++,k);
    }
}
