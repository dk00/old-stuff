#include<cstdio>
int s[30],p[30][3001],q[30][3001];
int abs(int n){return n>0?n:-n;}
main()
{
    int i,j,k,n;
    while(scanf("%d",&n) && n)
    {
        for(j=0;j<n;j++)
            for(k=3000;k>=0;k--)
                p[j][k]=q[j][k]=0;
        scanf("%d",&s[0]);
        p[0][s[0]]=1;
        for(i=1;i<n;i++)
        {
            for(j=0;j<=i;j++)
                scanf("%d",&s[j]),s[j]=abs(s[j]);
            for(j=i-1;j>=0;j--)
            {
                for(k=3000-s[j+1];k>=0;k--)
                    q[j+1][k+s[j+1]]|=p[j][k];
                for(k=3000;k>=0;k--)
                    q[j+1][abs(k-s[j+1])]|=p[j][k];
                for(k=3000-s[j];k>=0;k--)
                    q[j][k+s[j]]|=p[j][k];
                for(k=3000;k>=0;k--)
                    q[j][abs(k-s[j])]|=p[j][k];
            }
            for(j=i;j>=0;j--)
                for(k=0;k<=3000;k++)
                    p[j][k]=q[j][k],q[j][k]=0;
        }
        for(i--;i>=0;i--)
        {
            for(j=0;j<i;j++)
                scanf("%d",&s[j]),s[j]=abs(s[j]);
            for(j=i-1;j>=0;j--)
            {
                for(k=3000-s[j];k>=0;k--)
                    q[j][k+s[j]]|=p[j+1][k];
                for(k=3000;k>=0;k--)
                    q[j][abs(k-s[j])]|=p[j+1][k];
                for(k=3000-s[j];k>=0;k--)
                    q[j][k+s[j]]|=p[j][k];
                for(k=3000;k>=0;k--)
                    q[j][abs(k-s[j])]|=p[j][k];
            }
            for(j=i-1;j>=0;j--)
                for(k=0;k<=3000;k++)
                    p[j][k]=q[j][k],q[j][k]=0;
        }
        for(k=0;p[0][k]==0;k++);
        printf("%d\n",k);
    }
}
