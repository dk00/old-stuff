#include<cstdio>
const long long inf=1000000000000000000ll;
char notp[1001];
int m,p[300],s[300];
void go(int n)
{
    int i,j;
    for(i=0,j=n;i<m;i++)
        while(j%p[i]==0)j/=p[i],s[i]++;
}
main()
{
    int i,j,k,n,T,C=1;
    long long sum;
    char tmp[99];
    for(i=3,m=1,p[0]=2;i<1000;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<1000;j+=i*2)
            notp[j]=1;
        p[m++]=i;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",tmp);
        for(k=0;tmp[k];k++);
        for(i=0;i<m;i++)s[i]=1;
        for(;n>0;n-=k)
            go(n);
        for(i=0,sum=1;s[i] && i<m;i++)
            if(sum>inf/s[i])goto no;
            else sum*=s[i];
        printf("Case %d: %lld\n",C++,sum);
        continue;
    no: printf("Case %d: Infinity\n",C++);
    }
}
