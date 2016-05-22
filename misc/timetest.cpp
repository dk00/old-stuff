#include<ctime>
#include<cstdio>
#include<cstdlib>
int a[2][20001],b[2][20001],x[20001],y[20001];
main()
{
    int i,j,k,n,start;
    while(scanf("%d",&n)==1)
    {
        start=clock();
        for(i=1;i<n;i++)
            for(j=0;j<n;j++)
            {
                a[i%2][j]=(a[1-i%2][j]+abs(x[i-1]-x[i]))<?
                (b[1-i%2][i]+abs(y[i-1]-y[i]));
                /*b[i%2][j]=(b[1-i%2][j]+abs(y[i-1]-y[i]))<?
                (a[1-i%2][i]+abs(x[i-1]-x[i]));*/
                
            }
        i=clock()-start;
        j=i/1000,k=i%1000;
        printf("%d.%03d\n",j,k);
    }
}
