/*
PROB:clocks
LANG:C++
*/
#include<cstdio>
char cmd[][9]={"ABDE","ABC","BCEF","ADG","BDEFH","CFI","DEGH","GHI","EFHI"};
int s[9],u[9],p[27];
void test(int i)
{
    for(int j=0;cmd[i][j];j++)
        ++s[cmd[i][j]-'A']%=4;
}
void undo(int i)
{
    for(int j=0;cmd[i][j];j++)
        (s[cmd[i][j]-'A']+=3)%=4;
}
bool check()
{
    for(int i=0;i<9;i++)
        if(s[i])return 0;
    return 1;
}
char go(int d,int i=0)
{
    if(check())return 1;
    if(d<=0)return 0;
    for(;i<9;i++)
        if(u[i])
        {
            u[i]--,p[d-1]=i;
            test(i);
            if(go(d-1,i))return 1;
            undo(i);
            u[i]++;
        }
    return 0;
}
main()
{
    freopen("clocks.in","r",stdin);
    freopen("clocks.out","w",stdout);
    int i,j;
    for(i=0;i<9;i++)
        scanf("%d",s+i),(s[i]/=3)%=4,u[i]=3;
    for(i=0;i<=27;i++)
        if(go(i))break;
    printf("%d",p[--i]+1);
    while(i--)
        printf(" %d",p[i]+1);
    puts("");
}
