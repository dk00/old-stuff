#include<cstdio>
int dis(int a,int b)
{
    a^=b,b=0;
    while(a)b+=a%2,a/=2;
    return b;
}
main()
{
    freopen("hamming.in","r",stdin);
    freopen("hamming.out","w",stdout);
    int i,j,k,n,b,d,s[65];
    scanf("%d %d %d",&n,&b,&d);
    for(i=0,k=1;i<n;i++)
    {
        for(j=0;j<i;k++)
            for(j=0;j<i;j++)
                if(dis(s[j],k)<d)break;
        s[i]=k-1;
        printf("%d",k-1);
        if(i%10==9 || i==n-1)puts("");
        else putchar(' ');
    }
}
/*
PROB:hamming
LANG:C++
*/
