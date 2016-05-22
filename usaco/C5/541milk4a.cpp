/*
ID: s0000151
PROG: milk4
LANG: C++
*/
#include<stdio.h>
int dp[20001],num[20001];
    // dp[]: 上次倒入多少，0 表示無法達成
    // num[]: 倒出這個多牛奶最少要幾個容器
main()
{
    freopen("milk4.in","r",stdin);
    freopen("milk4.out","w",stdout);
    int i,k,n,q,pv,now;
    dp[0]=-1;
    scanf("%d %d",&q,&n);
    while(n--)
    {
        scanf("%d",&pv);
        for(i=pv;i<=q;i++)
        {
            if(dp[i-pv]==0)
                continue;
            now=num[i-pv]+1;
            if(dp[i-pv]==pv)
                now--;
            if(dp[i]==0 || now<num[i] || now<=num[i] && pv<dp[i])
            {
                dp[i]=pv;
                num[i]=now;
            }
        }
    }
    for(n=pv=0;dp[q]>0;q-=dp[q])
        if(pv!=dp[q])
        {
            num[n++]=dp[q];
            pv=dp[q];
        }
    for(i=0;i<n;i++)
        for(k=1;k<n;k++)
            if(num[k]<num[k-1])
                num[k]+=num[k-1],
                num[k-1]=num[k]-num[k-1],
                num[k]-=num[k-1];
    printf("%d",n);
    for(i=0;i<n;i++)
        printf(" %d",num[i]);
    puts("");
    //scanf(" ");
}
