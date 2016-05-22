#include<cstdio>
const int M=1000000009;
inline int pow(int n,int k)
{
    int i,a;
    for(a=1,i=1;i<=k;i*=2,n=n*n%M)
        if(i&k)a=a*n%M;
    return a;
}
main()
{
    for(i=1;i<20;i++)
        for(c[i][0]=j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(j=1;j<=n;j++)
            scanf("%d",s[0]+j),s[0][j]%=M;
        for(i=1;i<21;i++)
            for(j=1;j<=n;j++)
                s[i][j]=s[i-1][j]*1ll*j%M;
        for(i=0;i<21;i++)
            for(j=n-1;j>=1;j--)
                s[i][j]+=s[i][j+1];
        scanf("%d",&t);
        while(t--)
        {
            scanf("%d %d %d",&i,&n,&m);
            for(j=sum=0;j<m;j++)
                sum=0ll+sum+c[m][j]*1ll*pow(-i,j)%M*s[m-j][i];
        }
    }
}
