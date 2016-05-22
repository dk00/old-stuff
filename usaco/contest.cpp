/*
TASK:contest
LANG:C++
*/
#include<cstdio>
char c[101][101];
main()
{
    freopen("contest.in","r",stdin);
    freopen("contest.out","w",stdout);
    int i,j,k,n,m;
    scanf("%d %d",&n,&m);
    while(m--)
    {
        scanf("%d %d",&i,&j);
        c[i-1][j-1]=1;
    }
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(!c[i][j] && c[i][k] && c[k][j])
                    c[i][j]=1;
    for(i=k=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            if(i!=j && !c[i][j] && !c[j][i])break;
        if(j>=n)k++;
    }
    printf("%d\n",k);
}
