#include<cstdio>
#include<cmath>
const double e=exp(1);
int E(double n)
{
    if(n<3)return 1;
    return E(n-1)+E(n-e);
}
main()
{
    int n;
    while(scanf("%d",&n) && n>=0)
        printf("%d\n",E(n));
}
