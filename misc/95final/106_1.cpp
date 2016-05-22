#include<cstdio>
const double x[][3]={
    {0.5149,0.3244,0.1607},
    {0.2654,0.6704,0.0642},
    {0.0248,0.1248,0.8504}
};
struct px
{
    double c[3];
    void get()
    {
        int i,j;
        scanf("%lf %lf %lf",c,c+1,c+2);
        double tmp[3];
        for(i=0;i<3;i++)tmp[i]=c[i],c[i]=0;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                c[i]+=tmp[j]*x[i][j];
        printf("%.4lf %.4lf %.4lf\n",c[0],c[1],c[2]);
    }
}s[256][256];
main()
{
    freopen("in_1.txt","r",stdin);
    int i,j,n;
    double avg,sum;
    scanf("%d",&n);
    for(avg=i=0;i<n;i++)
    {
        for(sum=j=0;j<n;j++)
        {
            s[i][j].get();
            sum+=s[i][j].c[1];
        }
        avg+=sum/n;
    }
    printf("The average of Y is %.4lf\n",avg/n);
}
