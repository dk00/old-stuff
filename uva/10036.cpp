#include<cstdio>
main()
{
    int i,j,n,m,T;
    bool s[2][100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<m;i++)s[0][i]=s[1][i]=0;
        s[n%2][0]=1;
        while(n--)
        {
            scanf("%d",&j);
            if(j<0)j=-j;
            j%=m;
            for(i=0;i<m;i++)s[n%2][i]=0;
            for(i=0;i<m;i++)
                if(s[1-n%2][i])
                    s[n%2][(i+j)%m]=s[n%2][(i-j+m)%m]=1;
        }
        if(s[0][0])
            puts("Divisible");
        else
            puts("Not divisible");
    }
}
