#include<cstdio>
long long s[10001]={1};
main()
{
    int i,j,k;
    for(i=1;i<=21;i++)
        for(j=k=i*i*i;j<=10000;j++)
            s[j]+=s[j-k];
    while(scanf("%d",&i)==1)
        printf("%lld\n",s[i]);
}
