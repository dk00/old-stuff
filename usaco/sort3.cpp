#include<cstdio>
int c[4][4],num[4],s[1001];
main()
{
    freopen("sort3.in","r",stdin);
    freopen("sort3.out","w",stdout);
    int i,j,k,n,sum;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i),num[s[i]]++;
    num[3]+=num[2]+=num[1];
    for(i=1;i<=3;i++)
        for(j=num[i-1];j<num[i];j++)
            if(s[j]!=i)c[i][s[j]]++;
    for(i=1,sum=0;i<=3;i++)
        for(j=1;j<=3;j++)
            if(i!=j)
            {
                k=c[i][j]<?c[j][i];
                c[i][j]-=k,c[j][i]-=k;
                sum+=k;
            }
    for(i=1;i<=3;i++)
        sum+=c[1][i]*2;
    printf("%d\n",sum);
    scanf(" ");
}
/*
PROB:sort3
LANG:C++
*/
