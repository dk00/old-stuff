#include<cstdio>
char s[2][201];
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&m,&n);
        for(i=0;i<=m;i++)
            s[0][i]=s[1][i]=0;
        s[n%2][0]=1;
        while(n--)
        {
            for(i=0;i<=m;i++)
                s[n%2][i]=0;
            scanf("%d",&i);
            while(i--)
            {
                scanf("%d",&j);
                for(k=j;k<=m;k++)
                    if(s[1-n%2][k-j])
                        s[n%2][k]=1;
            }
        }
        for(i=m;!s[0][i] && i>=0;i--);
        if(i>=0)
            printf("%d\n",i);
        else
            puts("no solution");
    }
}
