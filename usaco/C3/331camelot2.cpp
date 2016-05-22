/*ID: s0000151
PROG: camelot
LANG: C++
*/
#include<stdio.h>
#define toX qx[i]+dx[d]
#define toY qy[i]+dy[d]
int i,j,d,c,r,kx,ky,max,cost[40][26],dist[40][26],pickup[40][26],king[40][26],
qx[1040],qy[1040],dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
void go(int x, int y){
    qx[0]=x;qy[0]=y;
    for(i=0;i<r;i++)for(j=0;j<c;j++)dist[i][j]=pickup[i][j]=1040;
    dist[x][y]=0;
    max=pickup[x][y]=(x-kx>?kx-x)>?(y-ky>?ky-y);
    for(i=0,j=1;i<j;i++)
        for(d=0;d<8;d++)
            if(toX>=0 && toX<r && toY>=0 && toY<c && dist[toX][toY]==1040){
                qx[j]=toX;
                qy[j++]=toY;
                dist[toX][toY]=dist[qx[i]][qy[i]]+1;
            }
}
void withking(int k){
    for(k=0;k<=max;k++)for(i=0;i<r;i++)for(j=0;j<c;j++)if(pickup[i][j]==k)
        for(d=0;d<8;d++)
            if(i+dx[d]>=0 && i+dx[d]<r && j+dy[d]>=0 && j+dy[d]<c)
                (pickup[i+dx[d]][j+dy[d]]<?=pickup[i][j]+1);
}
main(){
freopen("camelot.in","r",stdin);
freopen("camelot.out","w",stdout);
int knx,kny,min=10000;
char tmp[10];
scanf("%d %d",&r,&c);
scanf("%s %d",tmp,&kx);
ky=tmp[0]-'A';
kx--;
for(i=0;i<r;i++)
    for(j=0;j<c;j++)
        king[i][j]=(i-kx>?kx-i)>?(j-ky>?ky-j);
while(scanf("%s %d",tmp,&knx)==2){
    kny=tmp[0]-'A';
    knx--;
    go(knx,kny);
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            cost[i][j]+=dist[i][j];
    for(i=0;i<r;i++)
        for(j=0;j<c;j++){
            pickup[i][j]=dist[i][j]+((i-kx>?kx-i)>?(j-ky>?ky-j));
            if(pickup[i][j]<1040)max>?=pickup[i][j];
        }
    withking(0);
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            king[i][j]<?=pickup[i][j]-dist[i][j];
}
for(i=0;i<r;i++)
    for(j=0;j<c;j++)
        min<?=cost[i][j]+king[i][j];
printf("%d\n",min);
}
