#include<cstdio>
char map[][18]={
"*****************",
"*...*.......**..*",
"**..*....*.*.*..*",
"*......*.**.**.**",
"*..**...**..**.**",
"**.....**..*.*..*",
"*....*..........*",
"*.....****.*...**",
"****.*.*........*",
"*****************",},tmp[10][18];
char dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char go()
{
    int i,j,k;
    for(i=1;i<9;i++)
        for(j=1;j<16;j++)
        {
            tmp[i][j]=map[i][j];
            for(k=0;k<4;k++)
                if(map[i-dx[k]][j-dy[k]]=='s' && tmp[i][j]=='e')return 1;
                else if(map[i-dx[k]][j-dy[k]]=='f' &&(tmp[i][j]=='.' || tmp[i][j]=='s'))
                    tmp[i][j]='f';
                else if(map[i-dx[k]][j-dy[k]]=='s' && tmp[i][j]=='.')
                    tmp[i][j]='s';
        }
    for(i=1;i<9;i++)
        for(j=1;j<16;j++)
            map[i][j]=tmp[i][j];
    return 0;
}
main()
{
    int i,k,x,y;
    scanf("%d %d",&x,&y);
    map[x][y]='f';
    scanf("%d",&k);
    for(i=1;i<k;i++)go();
    scanf("%d %d",&x,&y);
    if(map[x][y]=='.')map[x][y]='s';
    scanf("%d %d",&x,&y);
    map[x][y]='e';
    for(k=0;k<=1000;k++)
        if(go())break;
    if(k<=1000)
        printf("%d\n",k+1);
    else
        puts("Help!");
    scanf(" ");
}
