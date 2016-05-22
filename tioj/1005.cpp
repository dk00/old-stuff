#include<cmath>
#include<cstdio>
#include<cstdlib>
#include< stdio.h >
const int test=5000000;
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    int i,j,k,n,sum,s[50];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for(i=sum=0;i<n;i++)
            for(j=i+1;j<n;j++)
                sum+=(gcd(s[i],s[j])==1);
        if(sum)
            printf("%.6lf\n",sqrt(6/(sum*1.0/(n*(n-1)/2))));
        else
            puts("No estimate for this data set.");
    }
}
