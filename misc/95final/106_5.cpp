#include<cstdio>
const int inf=2147483647;
int c[201][201],s[2][201][201];
main()
{
    freopen("in_5.txt","r",stdin);
    int i,j,k,l,p,q,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&c[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            s[0][i][j]=s[1][i][j]=inf;
    l=s[0][1][2]=0;
    for(p=0,q=1;scanf("%d",&k)==1;p=!p,q=!q)
    {
        k--;
        for(i=0;i<n;i++)
            for(j=i;j<n;j++)
                if(s[p][i][j]<inf)
                {
                    s[q][i][j]<?=s[p][i][j]+c[l][k];
                    s[q][j<?l][j>?l]<?=s[p][i][j]+c[i][k];
                    s[q][i<?l][i>?l]<?=s[p][i][j]+c[j][k];
                    s[p][i][j]=inf;
                }
        l=k;
    }
    k=inf;
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
            k<?=s[p][i][j];
    printf("%d\n",k);
}
