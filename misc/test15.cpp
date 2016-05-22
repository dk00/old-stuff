#include<cstdio>
main()
{
    int i,n;
    double p;
    while(scanf("%d",&n)==1){
        p=1.;
        for(i=1;i<n;i++)
            p*=(365.-i)/365;
        printf("%.3lf\n",1-p);
    }
}
