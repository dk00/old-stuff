#include<iostream>
using namespace std;
long long sn[25],dp[25][181];
long long inline gcd(long long a,long long b)
{
    while((a%=b) && (b%=a));
    return a+b;
}
main()
{
    long long i,j,k;
    int n,x;
    for(i=sn[0]=1;i<25;i++)
        sn[i]=sn[i-1]*6;
    dp[0][0]=1;
    for(i=0;i<24;i++)
        for(j=0;j<151;j++)
            for(k=1;k<=6;k++)
                dp[i+1][j+k]+=dp[i][j];
    for(i=0;i<=24;i++)
        for(j=151;j>=0;j--)
            dp[i][j]+=dp[i][j+1];
    while(1)
    {
        cin>>n>>x;
        if(n==0 && x==0)
            break;
        if(n>=x)
        {
            cout<<"1\n";
            continue;
        }
        if(n*6<x)
        {
            cout<<"0\n";
            continue;
        }
        if(n==0 && x==0)
            break;
        i=dp[n][x];
        j=sn[n];
        k=gcd(i,j);
        i/=k,j/=k;
        cout<<i;
        if(j>1)
            cout<<'/'<<j;
        cout<<'\n';
    }
}
