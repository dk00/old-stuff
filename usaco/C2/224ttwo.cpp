/*
ID: s0000151
PROG: ttwo
LANG: C++
*/

#include<stdio.h>
int dx[]={-1,0,1,0},dy[]={0,1,0,-1},cx,cy,fx,fy,cdir,fdir,nx,ny;
char grid[11][11];
void move(){
    nx=cx+dx[cdir];
    ny=cy+dy[cdir];
    if(nx<0 || nx>= 10 || ny<0 || ny>=10 || grid[nx][ny]=='*')
		cdir=(cdir+1)%4;
    else{
        cx=nx;
        cy=ny;
    }
    nx=fx+dx[fdir];
    ny=fy+dy[fdir];
    if(nx<0 || nx>= 10 || ny<0 || ny>=10 || grid[nx][ny]=='*')
		fdir=(fdir+1)%4;
    else{
        fx=nx;
        fy=ny;
    }
}
main(){
freopen("ttwo.in","r",stdin);
freopen("ttwo.out","w",stdout);
long i,j;char c;
for(i=0;i<10;i++){
    for(j=0;j<10;j++){
        scanf("%c",&grid[i][j]);
        if(grid[i][j]=='F'){
            fx=i;
            fy=j;
        }
        if(grid[i][j]=='C'){
            cx=i;
            cy=j;
        }
    }
    scanf("%c",&c);
}
for(cdir=fdir=i=0;i<160000 && (cx!=fx || cy!=fy);i++)move();
if(cx==fx && cy==fy)printf("%ld\n",i);
else printf("0\n");
//scanf(" ");
}
