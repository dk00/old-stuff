#include<cstdio>
int n;
char map[201][201];
bool isnode(char x)
{
    return(x && x!=' ');
}
void go(int x,int y)
{
    if(x>=n || y<0 || !map[x][y])return;
    printf("%c(",map[x][y]);
    if(x+1>=n || map[x+1][y]!='|')
    {
        printf(")");
        return;
    }
    while(y>0 && map[x+2][y-1]=='-')y--;
    while(map[x+2][y]=='-')
    {
        if(isnode(map[x+3][y]))
            go(x+3,y);
        y++;
    }
    printf(")");
}
main()
{
    int i,j,T;
    scanf("%d%c",&T,map[0]);
    while(T--)
    {
        for(i=0;i<200;i++)
            for(j=0;j<200;j++)
                map[i][j]=' ';
        for(n=0;gets(map[n]) && map[n][0]!='#';n++);
        for(i=0;i<n;i++)
        {
            for(j=0;map[i][j];j++)
                if(isnode(map[i][j]))
                    break;
            if(map[i][j])break;
        }
        printf("(");
        go(i,j);
        printf(")\n");
    }
}
