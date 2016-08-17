#include<cstdio>
int s[9][9],num[9][9],use[9][9][10];
bool mark(int x,int y,int p)
{
    int able=1;
    num[x][y]++;
    for(int i=0;i<9;i++)
    {
        if(use[x][i][p]==0)
            if(!s[x][i] && !--num[x][i])able=0;
        use[x][i][p]++;
        if(use[i][y][p]==0)
            if(!s[i][y] && !--num[i][y])able=0;
        use[i][y][p]++;
        if(use[x-x%3+i/3][y-y%3+i%3][p]==0)
            if(!s[x-x%3+i/3][y-y%3+i%3] && !--num[x-x%3+i/3][y-y%3+i%3])
                able=0;
        use[x-x%3+i/3][y-y%3+i%3][p]++;
    }
    num[x][y]--;
    return able;
}
void unmark(int x,int y,int p)
{
    for(int i=0;i<9;i++)
    {
        use[x][i][p]--;
        if(use[x][i][p]==0)
            num[x][i]++;
        use[i][y][p]--;
        if(use[i][y][p]==0)
            num[i][y]++;
        use[x-x%3+i/3][y-y%3+i%3][p]--;
        if(use[x-x%3+i/3][y-y%3+i%3][p]==0)
            num[x-x%3+i/3][y-y%3+i%3]++;
    }
}
bool dfs(int p)
{
    while(p<81 && s[p/9][p%9])p++;
    if(p>=81)return 1;
    for(int i=1;i<=9;i++)
        if(use[p/9][p%9][i]==0)
        {
            s[p/9][p%9]=i;
            if(mark(p/9,p%9,i) && dfs(p+1))
                return 1;
            unmark(p/9,p%9,i);
            s[p/9][p%9]=0;
        }
    return 0;
}
main()
{
    char tmp[1000];
    int i,j,k,t;
    scanf("%d",&t);
    while(t--)
    {
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            {
                num[i][j]=9;
                for(k=0;k<9;k++)
                    use[i][j][k]=0;
            }
        for(i=0;i<9;i++)
        {
            scanf("%s",tmp);
            for(j=0;j<9;j++)
            {
                if(tmp[j]!='.')
                {
                    s[i][j]=tmp[j]-'0';
                    mark(i,j,s[i][j]);
                }
                else s[i][j]=0;
            }
        }
        if(!dfs(0))
        {
            puts("No solution");
            continue;
        }
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(s[i][j])putchar(s[i][j]+'0');
                else putchar('.');
            }
            puts("");
        }
    }
}
