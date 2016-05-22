/*
ID: s0000151
PROG: starry
LANG: C++
*/
#include<stdio.h>
#include<string.h>
int h,w,e,cn,sx,sy,th,ch[26],
dx[]={0,1,1,1,0,-1,-1,-1},dy[]={1,1,0,-1,-1,-1,0,1};
char map[100][101],the[100][101],clu[26][8][100][101];
void go(int x,int y){
    if(x<0 || y<0 || x>=h || y>=w || map[x][y]!='1')return;
    map[x][y]++;
    e>?=y;
    th>?=(x-sx+1);
    the[sx-x][sy-y]=1;
    for(int i=0;i<8;i++)go(x+dx[i],y+dy[i]);
}
void fill(int x,int y,char what){
    if(x<0 || y<0 || x>=h || y>=w || map[x][y]!='2')return;
    map[x][y]=what;
    for(int i=0;i<8;i++)go(x+dx[i],y+dy[i]);
}
void empty(){
    int i,j;
    for(i=0;i<h;i++)
        for(j=0;j<w;j++)the[i][j]='0';
}
void copy(){
    int i,j,k;
    ch[cn]=th;
    for(i=0;i<th;i++)
        strcpy(clu[cn][0][i],the[i]);
    for(i=1;i<3;i++)
        for(clu[cn][i][e]='\0',j=0;j<th;j++)
            for(k=0;k<e;k++)
                clu[cn][i][j][k]=clu[cn][i-1][j][k];
}
int cmp(int s){
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<ch[s];j++)
            if(strcmp(clu[s][i][j],the[i])return 0;
    return 1;
}
void set(int x,int y){
    int i;
    for(i=0;i<h;i++)the[e+1]='\0';
    for(i=0;i<cn;i++)if(th==ch[i] && cmp(i))return;
    fill(x,y,cn+'a');
    ++cn;
    copy();
}
main(){
freopen("starry.in","r",stdin);
freopen("starry.out","w",stdout);
int i,j;
scanf("%d",&h,&w);
for(i=0;i<h;i++)scanf("%s",map[i]);
for(i=0;i<h;i++)
    for(j=0;j<w;j++)
        if(map[i][j]=='1'){
            sx=i;sy=j;
            go(i,j);
            set(i,j);
        }
for(i=0;i<h;i++)puts(map[i]);
}
