#include<cstdio>
int s1[501],s2[501];
int abs(int n){return n<0?-n:n;}
int S(int i,int j,int k,int l)
{return s[k][l]-s[k][j-1]-s[i-1][l]+s[i-1][j-1];}
int c(int i,int j,int k,int l,int m,int n)
{
    return c1[k][n]-c1[k][j-1]-c1[i-1][n]+c1[i-1][j-1]
          +c2[i][n]-c2[i][l+1]-c2[k+1][n]+c2[k+1][l+1]
          +c3[m][l]-c3[m][j-1]-c3[i-1][l]+c3[i-1][j-1]
          +c4[m][j]-c4[m][l+1]-c4[k+1][j]+c4[k+1][l=1];
}
main()
{
    int i,j,k,n,m,q,T,C;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&m,&q);
        for(i=0;i<=n+1;i++)
            for(j=0;j<=m+1;j++)
                s[i][j]=c1[i][j]=c2[i][j]=c3[i][j]=c4[i][j]=0;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                scanf("%d",&s[i][j]);
                s[i][j]+=s[i][j-1];
            }
        for(j=1;j<=m;j++)
            for(i=1;i<=n;i++)
                s[i][j]+=s[i-1][j];
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                c1[i][j]=c1[i][j-1]*2+S(1,j,i,j);
            for(j=m;j>0;j--)
                c2[i][j]=c2[i][j+1]*2+S(1,j,i,j);
        }
        for(j=1;j<=m;j++)
        {
            for(i=1;i<=n;i++)
                c3[i][j]=c3[i-1][j]*2+S(i,1,i,j);
            for(i=n;i>0;i--)
                c4[i][j]=c4[i+1][j]*2+S(i,1,i,j);
        }
        for(C=1;q--;C++)
        {
            scanf("%d %d %d %d",&i,&j,&n,&m);
            printf("%d %d\n",C,p1[i-1][n-1]+p2[j-1][m-1]);
        }
    }
}
