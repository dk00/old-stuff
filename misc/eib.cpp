#include"d:\a\bigint1.h"
#include<cmath>
const double e=exp(1);
bigint p;
int pn,pk;
bigint C(int n,int k)
{
    printf("%d %d\n",n,k);
    k<?=(n-k);
    while(pk<k)
        p*=(pn-pk),p/=++pk;
    while(pk>k)
        p*=pk,p/=pn+1-pk--;
    while(pn<n)
        p*=++pn,p/=pn-k;
    /*for(int i=0;i<k;i++)
        x*=n-i,x/=i+1;*/
    return p;
}
main()
{
    bigint a;
    int i,j,n;
    while(scanf("%d",&n) && n>=0)
    {
        a=0;
        p=pn=pk=1;
        for(i=0;n-i>=2;i++)
        {
            if(n-i>4)
            {
                j=(int)floor((n-i-2)/e);
                if(n-i-j*e<3)
                {
                    a+=C(i+j,j);
             //       printf("%d %d\n",i,j);
                }
            }
            if(n-i>2)
            {
                j=(int)floor((n-i)/e);
                while(n-i-j*e+e<3)j--;
                if(n-i-j*e<2)
                {
                    a+=C(i+j-1,j-1);
               //     printf("%d %d *\n",i,j);
                }
            }
            if(n-i==2)
            {
                a+=1;
              //  printf("%d 0\n",i);
            }
        }
        puts(a.tostr());
    }
}
