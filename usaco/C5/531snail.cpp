/*
ID: s0000151
PROG: snail
LANG: C++
*/
#include<stdio.h>
int n,max,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int map[122][122];
void dfs(int x,int y,int s,int d){
	map[x][y]=1;
	int i;
	if(map[x+dx[d]][y+dy[d]]==1){
        max>?=s;
        map[x][y]=0;
        return;
    }
	if(map[x+dx[d]][y+dy[d]]){
	    for(i=0;i<4;i++)
	        if(!map[x+dx[i]][y+dy[i]])dfs(x+dx[i],y+dy[i],s+1,i);
	    map[x][y]=0;
	    max>?=s;
		return;
	}
	dfs(x+dx[d],y+dy[d],s+1,d);
	map[x][y]=0;
}
main(){
freopen("snail.in","r",stdin);
freopen("snail.out","w",stdout);
int i,b;
char c,z;
scanf("%d %d%c",&n,&b,&z);
for(i=0;i<=n+1;i++)map[i][0]=map[0][i]=map[n+1][i]=map[i][n+1]=3;
while(b--){
	scanf("%c%d%c",&c,&i,&z);
	map[i][c-'A'+1]=2;
}

dfs(1,1,1,0);
dfs(1,1,1,1);
printf("%d\n",max);
}
