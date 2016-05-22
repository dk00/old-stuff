#include<cstdio>
main()
{
    unsigned i,n,l,u,a,j;
    while(scanf("%u %u %u",&n,&l,&u)==3)
    {
        for(a=0,i=j=1<<31;i>0;i>>=1,j|=i)
            if(((a<(l&j) || a>(u&j)) || (i&n)==0) &&
            (a|i)>=(l&j) && (a|i)<=(u&j))
                a|=i;
        printf("%u\n",a);
    }
}
