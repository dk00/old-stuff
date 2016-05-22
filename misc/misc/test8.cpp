#include<cstdio>
class a;
class b{
    a *ptr;
};
class a{
    b *ptr;
};
main()
{
    int i,j,k,n,m,s[99];
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<=n*m;i++)
            s[i]=0;
        s[0]=1;
        for(i=1;i<=m;i++)
        {
            for(j=n*i;j>=0;j--)
                for(k=(j-n)>?0;k<j;k++)
                    s[j]+=s[k];
            for(j=0;j<=i*n;j++)
                printf("%3d ",s[j]);
            puts("");
        }
    }
}
/*
1
1 1 1 1
*/
