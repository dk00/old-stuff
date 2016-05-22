#include<cstdio>
main()
{
    freopen("hailin.txt","r",stdin);
    freopen("hailout.txt","w",stdout);
    int i,n;
    while(scanf("%d",&n) && n)
    {
        for(i=0;n!=1;i++)
        {
            if(n%2)n=n*3+1;
            else n/=2;
        }
        printf("%d\n",i);
    }
}
