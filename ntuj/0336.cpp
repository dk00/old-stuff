#include<cstdio>
main()
{
    int i;
    double j,k,sum;
    for(sum=i=0;i<12;i++)
    {
        scanf("%lf",&j,&k);
        sum+=j;
    }
    sum/=12;
    printf("$%.2lf\n",sum);
}
