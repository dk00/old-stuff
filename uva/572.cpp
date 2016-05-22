#include<stdio.h>
int map[101][101],m,n,deposit;
void dfs(int x,int y){
    map[x][y]=0;
    if(x-1>=0 && y-1>=0 && map[x-1][y-1]) dfs(x-1,y-1);
    if(x-1>=0 && map[x-1][y]) dfs(x-1,y);
    if(y-1>=0 && map[x][y-1]) dfs(x,y-1);
    if(x-1>=0 && y+1<n && map[x-1][y+1]) dfs(x-1,y+1);
    if(y-1>=0 && x+1<m && map[x+1][y-1]) dfs(x+1,y-1);
    if(x+1<m && map[x+1][y]) dfs(x+1,y);
    if(y+1<n && map[x][y+1]) dfs(x,y+1);
    if(x+1<m && y+1<n && map[x+1][y+1]) dfs(x+1,y+1);
}
main(){
int i,j;
char c;
while(1){
    scanf("%d %d",&m,&n);
    if(m+n==0)break;
    for(i=0;i<m;i++){
        scanf("\n");
        for(j=0;j<n;j++){
            scanf("%c",&c);
            if(c=='*')map[i][j]=0;
            else map[i][j]=1;
        }
    }
    for(i=0,deposit=0;i<m;i++){
        for(j=0;j<n;j++){
            if(map[i][j]){
                deposit++;
                dfs(i,j);
            }
        }
    }
    printf("%d\n",deposit);
}
}
