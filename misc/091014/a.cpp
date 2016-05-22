#include<cmath>
#include<cstdio>
main()
{
    int T;
    double r0,r1,r2,pi=3.14159,s0,s1,s2;
    scanf("%d",&T);
    while(T--){
        scanf("%lf %lf",&r0,&r1);
        r2=sqrt(r0*r0+r1*r1)/2;
        r0/=2,r1/=2;
        s0=pi*r0*r0;
        s1=pi*r1*r1;
        printf("%lf %lf\n",acos(r0/r2),2*r0*r1);
        s2=2*acos(r0/r2)*r2*r2+2*acos(r1/r2)*r2*r2-2*r0*r1;
        printf("%lf %lf %lf %lf %lf %lf\n",r0,r1,r2,s0,s1,s2);
        printf("%.6lf\n",s2/(s0+s1));
    }
}

/*

0.78539816339744830961566084581988

*/
