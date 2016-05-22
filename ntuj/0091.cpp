#include<algorithm>
using namespace std;
int x[999];
long long s[99][99][2001];
main()
{
    int i,j,k,n,m,T,C=1;
    long long sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%d",x+i);
        sort(x,x+n);
        for(i=0;i<=n;i++)
            for(k=0;k<=n;k++)
                for(j=0;j<=m;j++)
                    s[i][k][j]=0;
        sum=0,s[0][0][0]=1;
        for(i=0;i<n;i++)
            for(k=0;k<n;k++)
                for(j=0;j<=m;j++)
                {
                    s[i+1][k][j]+=s[i][k][j];
                    if(j+x[i]<=m)
                    {
                        if(i==k)s[i+1][i+1][j+x[i]]+=s[i][k][j];
                        else s[i+1][k][j+x[i]]+=s[i][k][j];
                    }
                }
        for(k=0;k<n;k++)
            for(j=1;j<=m;j++)
                if(j+x[k]>m)sum+=s[n][k][j];
        printf("%d %I64d\n",C++,sum);
    }
}
