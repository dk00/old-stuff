#include<stdio.h>
int n,find,map[50][50],
    dx[]={2,1,-1,-2,-2,-1,1,2}, //表示不同的走法
    dy[]={1,2,2,1,-1,-2,-2,-1};
void dfs(int x,int y,int s){    //(x,y) 為位置，s 是目前步數
    if(s>=n*n)find=1;   //表示已經走完整個棋盤
    if(find)return;     //find 設為 1表示找到解
    int i,j,k;
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];    //判斷要走的地方是否超出棋盤
        if(i>=0 && j>=0 && i<n && j<n && map[i][j]==-1){//或已走過
            map[i][j]=s+1;  //如果可用，就標示並從(i,j)繼續走
            dfs(i,j,s+1);
            if(find)return; //如果這樣走有解的話，就結束搜尋
            map[i][j]=-1;
        }
    }
}
main(){
int i,j,x,y;
while(scanf("%d %d %d",&n,&x,&y) && n){
    find=0;                 //歸零
    for(i=0;i<n;i++)        //把整個圖設為沒走過
        for(j=0;j<n;j++)
            map[i][j]=-1;   // -1:沒走過 n(n>0): 第n步走到這格
    x--,y--;                //因為陣列是從(0,0)開始，所以-1
    map[x][y]=1;            //給定起始位置設為 1
    dfs(x,y,1);
    if(!find){              //找不到解
        puts("No solution");
        continue;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%3d",map[i][j]);
        puts("");
    }
}
}
