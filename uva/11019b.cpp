#include<cstdio>
char s[1000][1001],s0[100][101];
main()
{
    int i,j,k,l,n,m,t,sum,tmp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        scanf("%d %d",&m,&i);
        for(i=0;i<m;i++)
            scanf("%s",s0[i]);
        for(i=sum=0;i<n;i++)
            for(j=0;s[0][j];j++)
            {
                for(tmp=1,k=0;tmp && k<m;k++)
                    for(l=0;tmp && s0[0][l];l++)
                        tmp&=(s[i+k][j+l]==s0[k][l]);
                sum+=tmp;
            }
        printf("%d\n",sum);
    }
}
