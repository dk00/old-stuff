/*
ID: s0000151
PROG: betsy
LANG: C++
*/
#include<stdio.h>
int n,path,pt,map[9][9],nb[9][9],row[9],col[9],
dx[]={1,0,-1,0},dy[]={0,1,0,-1};
void dfs(int x,int y,int left){
    pt++;
    if(x==n && y==1){
        if(!left)path++;
        return;
    }
    if(y>=n && !map[x-1][n])return;
    if(x>=n && !map[n][y+1])return;
    if(y==1 && !map[x-1][1])return;
    if(x==1 && !map[1][y-1])return;
    if(row[y-1]>=n || col[x+1]>=n)return;
    if(x==2 && y==2 && n*n==left+3){
        if(map[x-1][y]){
            map[x][y-1]=1;
            row[y-1]++;
            col[x]++;
            dfs(x,y-1,left-1);
            map[x][y-1]=0;
            row[y-1]--;
            col[x]--;
        }
        else{
            row[y]++;
            col[x-1]++;
            map[x-1][y]=1;
            dfs(x-1,y,left-1);
            map[x-1][y]=0;
            row[y]--;
            col[x-1]--;
        }
        return;
    }
    int i,v=-1;
    for(i=0;i<4;i++)
        if((++nb[x+dx[i]][y+dy[i]])*(!map[x+dx[i]][y+dy[i]])>=3){
            if(v>=0){
                for(;i>=0;i--)--nb[x+dx[i]][y+dy[i]];
                return;
            }
            else v=i;
        }
    for(i=0;i<4 && v<0;i++)
        if(!map[x+dx[i]][y+dy[i]]){
            map[x+dx[i]][y+dy[i]]=1;
            col[x+dx[i]]++;
            row[y+dy[i]]++;
            dfs(x+dx[i],y+dy[i],left-1);
            map[x+dx[i]][y+dy[i]]=0;
            col[x+dx[i]]--;
            row[y+dy[i]]--;
        }
    if(v>=0){
        col[x+dx[v]]++;
        row[y+dy[v]]++;
        map[x+dx[v]][y+dy[v]]=1;
        dfs(x+dx[v],y+dy[v],left-1);
        map[x+dx[v]][y+dy[v]]=0;
        col[x+dx[v]]--;
        row[y+dy[v]]--;
    }
    for(i=0;i<4;i++)--nb[x+dx[i]][y+dy[i]];
}
main(){
//freopen("betsy.in","r",stdin);
//freopen("betsy.out","w",stdout);
int i,j;
while(scanf("%d",&n)!=EOF){
for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)nb[i][j]=map[i][j]=0;
for(i=0;i<=n+1;i++){
    map[0][i]=map[n+1][i]=map[i][0]=map[i][n+1]=1;
    col[i]=row[i]=0;
}
path=pt=0;
col[1]=row[1]=map[1][1]=1;
nb[1][2]=nb[2][1]=1;
dfs(1,1,n*n-1);
printf("%d/%d\n",path,pt);
}
}
//88418 1770 86 8 2 1 1
