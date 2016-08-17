#include<cmath>
#include<cstdio>
double s0[501][501],s1[501][501];
main()
{
    int i,j,n;
    double p,res;
    while(scanf("%d %lf",&n,&p) && n)
    {
        for(i=1;i<=n;i++)
        {
            s0[i][0]=s1[i][0]=1,
            s0[i][1]=1-p,s1[i][1]=p;
            for(j=2;j<=n;j++)
            {
                s0[i][j]=(1-p)*(s0[i][j-1]+s1[i][j-1]);
                s1[i][j]=p*(s0[i][j-1]+s1[i][j-1]);
                if(j>i)s1[i][j]-=pow(p,1.0+i)*s0[i][j-i-1];
            }
        }
        for(i=1,res=0;i<=n-1;i++)
            res-=s0[i][n]+s1[i][n];
        res+=n*(s0[n][n]+s1[n][n])-pow(1-p,n);
        printf("%.6lf\n",res);
    }
}
