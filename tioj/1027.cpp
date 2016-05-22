#include<cmath>
#include<cstdio>
long long cmp(long long x,long long a,long long b)
{
    return x*b*b-a*a;
}
main()
{
    int i,j,m;
    long long a,b,c,d;
    while(scanf("%d %d",&i,&m))
    {
        a=b=c=1,d=0;
        while(m--)
        {
            j=cmp(i,a+c,b+d);
            if(!j)break;
            if(j<0)
                c+=a,d+=b;
            else
                a+=c,b+=d;
        }
        printf("%I64d/%I64d\n",a+c,b+d);
    }
}
