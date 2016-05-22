#include<cmath>
#include<cstdio>
main()
{
    int i,j,b;
    double n,x;
    while(scanf("%d %lf",&b,&n)==2)
    {
        printf("%.0lf.",floor(n));
        n=n-floor(n);
        for(i=0,x=1.0/b;i<6;i++,x/=b)
        {
            for(j=0;n>=x;j++,n-=x);
            printf("%d",j);
        }
        puts("");
    }
}
