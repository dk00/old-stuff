#include<cstdio>
long long s[101][101];
main()
{
    int i,j,n,T,C=1;
    char tmp[99];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %s %d",tmp,tmp,&n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%lld",&s[i][j]);
        for(i=0;i<n;i++)
            for(j=i;j<n-i;j++)
                if(s[i][j]<0 || s[i][j]!=s[n-i-1][n-j-1] || s[j][i]!=s[n-j-1][n-i-1])
                    goto no;
        printf("Test #%d: Symmetric.\n",C++);
        continue;
    no: printf("Test #%d: Non-symmetric.\n",C++);
    }
}
