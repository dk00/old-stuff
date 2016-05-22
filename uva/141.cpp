#include<stdio.h>
int n,sn,stat[1000][50],now[50];
int match(int k){
    for(int i=0;i<n;i++)
        if(stat[k][i]!=now[i])return 0;
    return 1;
}
int set(){
int i,j;
    for(i=0;i<sn;i++)
        if(match(i))return 1;
    for(i=0;i<n;i++)
        stat[sn][i]=stat[sn+1][i]=stat[sn+2][i]=stat[sn+3][i]=0;
    for(i=0;i<n;i++)
        for(stat[sn][i]=now[i],j=0;j<n;j++)
            if(now[i]&(1<<j)){
                stat[sn+1][j]|=(1<<(n-i-1));
                stat[sn+2][n-i-1]|=(1<<(n-j-1));
                stat[sn+3][n-j-1]|=(1<<i);
            }
    sn+=4;
    return 0;
}
main(){
int i,j,x,y,draw;
char c[100];
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)now[i]=0;
    for(i=sn=draw=1;i<=n*2;i++){
        scanf("%d %d %s",&x,&y,c);
        if(!draw)continue;
        x--,y--;
        if(*c-'-')now[x]|=(1<<y);
        else now[x]&=~(1<<y);
        if(set()){
            printf("Player %d wins on move %d\n",(i&1)+1,i);
            draw=0;
        }
    }
    if(draw)puts("Draw");
}
}
