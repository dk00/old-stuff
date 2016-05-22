#include<ctime>
#include<cstdio>
const long long Max=1000000000000000ll;
int pr[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
long long test[5001],u;
inline void go(int i,int p,int q,long long num)
{
    if(num>Max || i>13 || p>5000)return;
    if(!num || !p)
    {
        puts("!");
        scanf(" ");
    }
    if(!test[p])
        test[p]=num;
    test[p]<?=num;
    go(i,p+q,q,num*pr[i]);
    go(i+1,p,p,num);
}
main()
{
    int i,C=1;
    go(0,1,1,1);
    for(i=0;i<=5000;i++)
    {
        printf("%I64dll,",test[i]);
        if(i%10==9)puts("");
    }
    while(scanf("%d",&i) && i)
    {
        if(test[i])
            printf("Case %d: %lld\n",C++,test[i]);
        else
            printf("Case %d: Impossible\n",C++);
    }
}
