#include<cmath>
#include<cstdio>
main()
{
    int i,j,a,b;
    double p,q;
    while(scanf("%d %d",&a,&b) && a+b)
    {
        i=(int)floor(sqrt(8.0*a+1));
        if(a<1 || i*i!=8*a+1 || int(2*a+1-sqrt(8*a+1))%2)
        {
            puts("No. of red balls invalid");
            continue;
        }
        p=(-1-2*a);
        q=a*a-a;
        i=int(2*a+1-sqrt(8*a+1))/2;
        j=int(2*a+1+sqrt(8*a+1))/2;
        if(b*10<7*i || i<b || i<1)i=-1;
        if(b*10<7*j || j<b || j<1)j=-1;
        if(i<0 && j<0)
        {
            puts("No. of black balls invalid");
            continue;
        }
        if(i>=0 && j>=0)printf("%d %d\n",i-b,j-b);
        else if(i>=0)printf("%d\n",i-b);
        else printf("%d\n",j-b);
    }
}
