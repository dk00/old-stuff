#include<algorithm>
long long f[50];
long long go(int num[],int n,int t)
{
    int i,j,k;
    long long s1[25],s2[25];
    if(n<=1)return 1;
    for(j=0;j<=t;j++)s1[j]=0;
    for(j=0;j<=num[0] && j<=t;j++)
        s1[j]=f[t]/f[j];
    for(i=1;i<n;i++)
    {
        for(j=0;j<=t;j++)s2[j]=0;
        for(j=0;j<=num[i] && j<=t;j++)
            for(k=0;j+k<=t;k++)
                s2[j+k]+=s1[k]/f[j];
        for(j=0;j<=t;j++)s1[j]=s2[j];
    }
    return s1[t];
}
int count(int s[],int n,int num[])
{
    int i,j;
    std::sort(s,s+n);
    for(i=j=0;i<n;j++)
    {
        s[j]=s[i];
        for(num[j]=0;i<n && s[i]==s[j];i++)num[j]++;
    }
    return j;
}
void make(int s1[],int u1[],const int& n1,int s2[],int n2,long long k)
{
    int i,j;
    long long l;
    for(i=0;i<n2;i++)
        for(j=0;j<n1;j++)
        {
            if(!u1[j])continue;
            s2[i]=s1[j],u1[j]--;
            l=go(u1,n1,n2-i-1);
            if(k<=l)break;
            k-=l,u1[j]++;
        }
}
long long get(int s1[],int u1[],int n1,int s2[],int n2)
{
    int i,j;
    long long k=0;
    for(i=0;i<n2;i++)
        for(j=0;j<n1;j++)
        {
            u1[j]--;
            if(s2[i]==s1[j])break;
            k+=go(u1,n1,n2-i-1);
            u1[j]++;
        }
    return k;
}
