#include<cmath>
#include<cstdio>
double s[262144];
main()
{
    int n;
    for(n=0;scanf("%lf",s+n)==1;n++);
    while(n--)
        printf("%.4lf\n",sqrt(s[n]));
}
