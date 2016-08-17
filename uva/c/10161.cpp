#include<cmath>
#include<cstdio>
main()
{
    int i,j,n;
    while(scanf("%d",&n) && n)
    {
        i=floor(sqrt(n));
        if(i*i==n)i--;
        j=n-i*i;
        if(j>i+1)
        {
            j=2*i+2-j;
            if(i++%2)printf("%d %d\n",i,j);
            else printf("%d %d\n",j,i);
        }else
        {
            if(i++%2)printf("%d %d\n",j,i);
            else printf("%d %d\n",i,j);
        }
        
    }
}
