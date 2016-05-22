#include<cstdio>
float s[10][100],a[10][100];
main()
{
    int i,j,k,n;
    for(k=0;k<10;k++)
    {
        for(j=0;j<=k;j++)
            s[j][0]=10000.0/(k+1.0);
        for(i=1;i<100;i++)
        {
            s[0][i]=(s[0][i-1]+s[1][i-1])/(k+1.0);
            for(j=1;j<k;j++)
                s[j][i]=(s[j-1][i-1]+s[j][i-1]+s[j+1][i-1])/(k+1.0);
            s[k][i]=(s[k][i-1]+s[k-1][i-1])/(k+1.0);
            for(j=0;j<=k;j++)
                a[k][i]+=s[j][i];
        }
    }
    while(scanf("%d %d",&k,&n)==2)
        printf("%.5lf\n",a[k][n-1]/100.000);
}
