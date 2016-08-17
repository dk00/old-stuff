#include<cstdio>
#include<cstring>
const char dx[]={1,1,1,0,-1,-1,-1,0},dy[]={-1,0,1,1,1,0,-1,-1};
char map[103][103];
main()
{
    int i,j,k,l,n,m,C=0;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        memset(map,0,sizeof(map));
        for(i=1;i<=n;i++)
            scanf("%s",map[i]+1);
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                for(k=l=0;k<8;k++)
                    if(map[i+dx[k]][j+dy[k]]=='*')l++;
                if(map[i][j]=='.')
                    map[i][j]='0'+l;
            }
        if(C++)puts("");
        printf("Field #%d:\n",C);
        for(i=1;i<=n;i++)
            puts(map[i]+1);
    }
}
