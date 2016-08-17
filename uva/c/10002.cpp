#include<cstdio>
main()
{
    int i,j,k,n;
    double x,y;
    while(scanf("%d",&n) && n>2)
    {
        for(x=y=i=0;i<n;i++)
        {
            scanf("%d %d",&j,&k);
            x+=j,y+=k;
        }
        x/=n,y/=n;
        printf("%.3lf %.3lf\n",x+1e-8,y+1e-8);
    }
}
