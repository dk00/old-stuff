#include<cstdio>
template<class x>x abs(x a){return a<0?-a:a;}
int s[201];
double t[201][201],c[201][201];
void print(double s[201][201],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%2lf ",s[i][j]);
        puts("");
    }
}
double calc(int a,int b)
{
    double sum=0;
    int i,x=s[b]-s[a];
    double y=b-a;
    for(i=a+1;i<b;i++)
        sum+=abs(s[a]+x*(i-a)/y-s[i]);
    return sum;
}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        for(i=0;i<n;i++)
            for(j=i+2;j<n;j++)
                c[i][j]=calc(i,j);
        for(i=0;i<=m;i++)
            for(j=0;j<n;j++)
                t[i][j]=10e20;
        for(j=0;j<n;j++)
            t[2][j]=c[0][j];
        for(i=3;i<=m;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                    t[i][j]<?=t[i-1][k]+c[k][j];
        printf("%.4lf\n",t[m][n-1]/n);
    }
}
