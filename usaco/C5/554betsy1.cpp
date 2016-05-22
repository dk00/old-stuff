/*
ID: s0000151
PROG: betsy
LANG: C++
*/
#include<stdio.h>
#include<time.h>
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
            dfs(x+dx[i],y+dy[i],left-1);
            map[x+dx[i]][y+dy[i]]=0;
        }
    if(v>=0){
        map[x+dx[v]][y+dy[v]]=1;
        dfs(x+dx[v],y+dy[v],left-1);
        map[x+dx[v]][y+dy[v]]=0;
    }
    for(i=0;i<4;i++)--nb[x+dx[i]][y+dy[i]];
}
main(){
//freopen("betsy.in","r",stdin);
//freopen("betsy.out","w",stdout);
int i,j;
double start;
while(scanf("%d",&n)!=EOF){
start=clock();
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
printf("%d/%d(%.3lf)\n",path,pt,(double)(clock()-start)/CLK_TCK);
}
}
//88418 1770 86 8 2 1 1
