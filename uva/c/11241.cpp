#include<cmath>
#include<cstdio>
main()
{
    char tmp[3];
    double T,D,H,x;
    while(scanf("%s %lf",tmp,&x) && tmp[0]!='E')
    {
        T=D=H=1e50;
        if(tmp[0]=='T')T=x;
        if(tmp[0]=='D')D=x;
        if(tmp[0]=='H')H=x;
        scanf("%s %lf",tmp,&x);
        if(tmp[0]=='T')T=x;
        if(tmp[0]=='D')D=x;
        if(tmp[0]=='H')H=x;
        if(T>1e49)
            T=H-0.5555*(6.11*exp(5417.7530*((1/273.16)-(1/(D+273.16))))-10);
        if(D>1e49)
            D=1.0/(1.0/273.16-log(((H-T)/0.5555+10)/6.11)/5417.7530)-273.16;
        if(H>1e49)
            H=T+0.5555*(6.11*exp(5417.7530*((1/273.16)-(1/(D+273.16))))-10);
        printf("T %.1lf D %.1lf H %.1lf\n",T,D,H);
    }
}
