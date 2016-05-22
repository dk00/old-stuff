#include<cstdio>
int s[300],t[300][300],u[300][300],v[300][300],r[32][300];
main()
{
    int i,j,k,n,m;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",&s[i]);
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
        {
            if(j>i)
                v[i][j]=v[i][j-1];
            else v[i][j]=0;
            v[i][j]+=s[j]-s[i];
        }
    for(i=n-1;i>=0;i--)
        for(j=i;j>=0;j--)
        {
            if(j<i)
                u[j][i]=u[j+1][i];
            else u[j][i]=0;
            u[j][i]+=s[i]-s[j];
        }
    if(0)
    {
        for(i=0;i<n;i++)
            for(j=i;j<n;j++)
            {
                t[i][j]=u[i][i]+v[i][j];
                for(k=i;k<=j;k++)
                    if(u[i][k]+v[k][j]<t[i][j])
                        t[i][j]=u[i][k]+v[k][j];
            }
    }
    else
    {
        int a,b,c;
        for(i=0;i<n;i++)
            for(j=i;j<n;j++)
            {
                int st,ed;
                st=i,ed=j;
                while(1)
                {
                    k=(st+ed)/2;
                    if(k>i)
                        a=u[i][k-1]+v[k-1][j];
                    else a=0;
                    if(k<j)
                        b=u[i][k+1]+v[k+1][j];
                    c=u[i][k]+v[k][j];
                    if(a>=c && b>=c)
                        break;
                    if(a>=c)
                        st=k+1;
                    else
                        ed=k-1;
                }
                t[i][j]=c;
                /*for(k=i;k<=j;k++)
                    if(u[i][k]+v[k][j]<t[i][j])
                        t[i][j]=u[i][k]+v[k][j];*/
            }
    }
    for(i=0;i<n;i++)
        r[1][i]=t[0][i];
    for(k=2;k<=m;k++)
        for(i=0;i<n;i++)
        {
            r[k][i]=2000000000;
            for(j=0;j<i;j++)
                r[k][i]<?=(r[k-1][j]+t[j+1][i]);
        }
    printf("%d\n",r[m][n-1]);
}
