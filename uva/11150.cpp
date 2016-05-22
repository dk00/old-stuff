#include<cstdio>
main()
{
    int i,j,k,n,max;
    while(scanf("%d",&n)==1)
    {
        for(i=n,j=1,max=0,k=0;i;)
            k+=i,i+=j,j=i%3,i/=3;
        max>?=k;
        for(i=n,j=2,k=0;i>3;)
            k+=i,i+=j,j=i%3,i/=3;
        max>?=k+i;
        printf("%d\n",max);
    }
}
