#include<cstdio>
int s[1000],c[10][10];
int go1(int n);
int go2(int n);
int add(int n);
int sub(int n);
int mul(int n);
int div(int n);
int go1(int n)
{
    if(n==1)return 1;
    int i,sum=0;
    for(i=1;i<n;i++)
    {
        sum+=c[n][i]*go1(i)*go2(n-i);   // +
        sum+=c[n][i]*go1(i)*go2(n-i);   // -
        sum+=c[n][i]*go1(i)*go2(n-i);   // *
        sum+=c[n][i]*go1(i)*go2(n-i);   // /
    }
    return sum;
}
int go2(int n)
{
    if(n==1)return 1;
    int i,sum=0;
    for(i=1;i<n;i++)
    {
        //sum+=c[n][i]*go1(i)*go2(n-i);   // +
        sum+=c[n][i]*go1(i)*go2(n-i);   // -
        sum+=c[n][i]*go1(i)*go2(n-i);   // *
        sum+=c[n][i]*go1(i)*go2(n-i);   // /
    }
    return sum;
}
main()
{
    int i,j,n;
    s[1]=c[0][0]=1;
    for(i=1;i<7;i++)
    {
        for(j=0;j<=i;j++)
            printf("%d ",c[i][j]=((j?c[i-1][j-1]:0)+c[i-1][j],1));
        puts("");
    }
    while(scanf("%d",&n) && n)
        printf("%d\n",go1(n));
}
