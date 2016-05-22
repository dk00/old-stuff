#include<cstring>
const int N=100000;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
    static int num[N];
    int i;
    for(i=0;i<=m;i++)num[i]=0;
    for(i=0;i<n;i++)num[x[t0[i]]+1]++;
    for(i=1;i<=m;i++)num[i]+=num[i-1];
    for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}

void suffixarray(char text[],int t[],int m)
{
    int i,j,k,n;
    static int s[N],tmp[N];
    for(n=0;text[n];n++)s[n]=text[n],t[n]=n;
    for(i=n;i<n*2;i++)s[i]=0,t[i]=n;
    for(i=1;i<n;i*=2)
    {
        rsort(s+i,t,tmp,n,m);
        rsort(s,tmp,t,n,m);
        for(j=0;j<n;j++)tmp[j]=s[j];
        for(j=0,m=1;j<n;j++)
        {
            s[t[j]]=m;
            if(tmp[t[j]]!=tmp[t[j+1]] || tmp[t[j]+i]!=tmp[t[j+1]+i])m++;
        }
    }
}
#include<cstdio>
main()
{
    int i,s[999];
    char t[999];
    while(~scanf("%s",t))
    {
        suffixarray(t,s,128);
        
        for(i=0;t[i];i++)
            printf("%d %d %s\n",s[i],d[i],t+s[i]);
    }
}
