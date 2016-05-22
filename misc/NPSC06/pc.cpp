#include<cstdio>
#include<algorithm>
bool s[2][1048576];
main()
{
    freopen("pc.in","r",stdin);
    freopen("pc.out","w",stdout);
    int i,j,k,n;
    while(scanf("%d",&n)==1 && n)
    {
        for(j=0;j<1048576;j++)
            s[0][j]=s[1][j]=0;
        s[0][0]=s[1][0]=1;
        for(i=0;n--;i=!i)
        {
            scanf("%d",&k);
            for(j=0;j<1048576;j++)
                if(s[i][j])
                    s[!i][j]=s[!i][j^k]=1;
        }
        for(i=1048575;i>=0;i--)
            if(s[0][i] || s[1][i])break;
        printf("%d\n",i);
    }
}
