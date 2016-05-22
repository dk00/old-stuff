#include<cstdio>
main()
{
    int i,j,n,m,ex,ey,T,c[32][32][2];
    long long s[32][32];
    char tmp[100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                s[i][j]=c[i][j][0]=c[i][j][1]=0;
        scanf("%d %d %d %d",&i,&j,&ex,&ey);
        s[i-1][j-1]++;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d %s",&i,&j,tmp);
            if(tmp[0]=='N')
                c[i-1][j][1]=1;
            if(tmp[0]=='S')
                c[i-1][j-1][1]=1;
            if(tmp[0]=='W')
                c[i-1][j-1][0]=1;
            if(tmp[0]=='E')
                c[i][j-1][0]=1;
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(!c[i+1][j][0])
                    s[i+1][j]+=s[i][j];
                if(!c[i][j+1][1])
                    s[i][j+1]+=s[i][j];
            }
        printf("%lld\n",s[ex-1][ey-1]);
    }
}
