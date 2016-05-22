/*
PROB:milk3
LANG:C++
*/
#include<cstdio>
char s[21][21];
int a,b,c;
void go(int x,int y,int z)
{
    if(s[y][z])return;
    s[y][z]=1;
    go(x+y-((x+y)<?b),(x+y)<?b,z);
    go((x+y)<?a,x+y-((x+y)<?a),z);
    go((x+z)<?a,y,x+z-((x+z)<?a));
    go(x+z-((x+z)<?c),y,(x+z)<?c);
    go(x,(y+z)<?b,y+z-((y+z)<?b));
    go(x,y+z-((y+z)<?c),(y+z)<?c);
}
main()
{
    freopen("milk3.in","r",stdin);
    freopen("milk3.out","w",stdout);
    scanf("%d %d %d",&a,&b,&c);
    go(0,0,c);
    for(int i=0;i<c;i++)
        if(s[c-i][i])printf("%d ",i);
    printf("%d\n",c);
    scanf(" ");
}
