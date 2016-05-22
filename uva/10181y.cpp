#include<stdio.h>
/*
use 0:nothing 1:now moving 2:stoped 3:locked
move::step find short path to space through 0
esc: find
*/
int map[4][4],use[4][4],p[16][2],q[16][2];
fnl[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}},
od[]={4,3,2,1,5,9,13,14,10,6,7,8,12,11,15};
void move(int n,int x,int y,int gx,int gy){
    while(x!=gx || y!=gy){
        if(x<gx)up=step(
    }
}
main(){
scanf("%d",&t);
while(t--){
    for(i=0;i<4;i++)
        for(j=0;j<4;j++){
            scanf("%d %d",&map[i][j]);
            p[map[i][j]][0]=i;
            p[map[i][j]][1]=j;
            q[fnl[i][j]][0]=i;
            q[fnl[i][j]][1]=i;
        }
    for(i=0;i<15;i++)
        move(od[i],p[od[i]][0],p[od[i]][1],q[od[i]][0],q[od[i]][1]);
}
}
