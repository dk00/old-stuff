#include<stdio.h>
const int cn=3;
int s[20][6],num[20][6];
void dfs(int x,int y)
{
    if(x>=5)
        return;
    if(y>=5)
    {
        dfs(x+1,0);
        return;
    }
    for(int i=0;i<cn;i++)
        if((!x || s[x-1][y]!=i) && (!y ||s[x][y-1]!=i))
        {
            s[x][y]=i;
            num[x][y]++;
            dfs(x,y+1);
        }
}
main()
{
    s[0][0]=0,num[0][0]=1;
    dfs(0,0);
    int i,l;
    for(l=0;l<4;l++)
    {
        for(i=0;i<6;i++)
            printf("%d ",num[l][i]);
        puts("");
    }
    getchar();
}
