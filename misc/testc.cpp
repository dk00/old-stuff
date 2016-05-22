#include<cstdio>
long long c[51][51];
main()
{
    int i,j,n;
    double x;
    for(i=0;i<=50;i++)
        c[i][0]=1;
    for(i=1;i<=50;i++)
        for(j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    while(scanf("%lf %d",&x,&n)==2)
        for(i=5;i<=10;i++)
            printf("%d:%lf\n",i,x*c[40-n][i-n]/c[40][i]);
}
