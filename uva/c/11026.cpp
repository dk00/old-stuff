#include<cstdio>
int s[1000];
long long f[2][1000];
main()
{
    int i,j,n,m,max;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=max=0;i<n;i++)
            scanf("%d",&s[i]),f[0][i]=1,f[1][i]=0;
        for(j=1;j<=n;j++)
        {
            if(j-2>=0)
                f[j%2][j-1]=f[!(j%2)][j-2]*s[j-1]%m;
            else f[j%2][j-1]=s[j-1];
            for(i=j;i<n;i++)
                f[j%2][i]=(f[j%2][i-1]+s[i]*f[!(j%2)][i-1]%m)%m;
            if(f[j%2][n-1]%m>max)
                max=f[j%2][n-1]%m;
        }
        printf("%d\n",max);
    }
}
