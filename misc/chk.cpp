#include<cstdio>
main()
{
    double a,b;
    FILE *f0=fopen("out","r"),*f1=fopen("k.out","r");
    while(fscanf(f0,"%lf",&a)==1 && fscanf(f1,"%lf",&b)==1)
        if(a-b>1e-8 || b-a>1e-8)
            printf("%.10lf %.10lf\n",a,b);
}
