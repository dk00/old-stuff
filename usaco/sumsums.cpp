/*
TASK:sumsums
LANG:C++
*/
#include<cstdio>
const int M=98765431;
long long s1[50001],s2[50001];
void inline
go(long long& a,long long& b,long long a1,long long a2,long long b1,long long b2)
{
    long long la=a,lb=b;
    a=((la*a1)%M+(lb*a2)%M)%M;
    b=((la*b1)%M+(lb*b2)%M)%M;
}
main()
{
    int i,n,t;
    long long j,a,b,c,d,x,sum;
    freopen("sumsums.in","r",stdin);
    freopen("sumsums.out","w",stdout);
    scanf("%d %d",&n,&t);
    for(i=sum=0;i<n;i++)
        scanf("%lld",s1+i),sum+=s1[i];
    for(i=0;i<n;i++)
        s2[i]=sum-s1[i];
    for(i=0;i<n;i++)
        s1[i]%=M,s2[i]%=M;
    a=0,b=1,c=n-1,d=n-2;
    for(i=1;i<=t;i*=2)
    {
        if(i&t)for(j=0;j<n;j++)
            go(s1[j],s2[j],a,b,c,d);
        x=b*c%M;
        (b*=(a+d)%M)%=M;
        (c*=(a+d)%M)%=M;
        (((a*=a)%=M)+=x)%=M;
        (((d*=d)%=M)+=x)%=M;
    }
    for(i=0;i<n;i++)
        printf("%lld\n",s1[i]);
}
