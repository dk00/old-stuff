#include<stdio.h>
int n,tmp,find,rem[8],map[50][50],
    dx[]={2,1,-1,-2,-2,-1,1,2},
    dy[]={1,2,2,1,-1,-2,-2,-1};
int test(int x,int y,int s){
    int i,j,k,sum=1;
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];
        if(i>=0 && j>=0 && i<n && j<n && map[i][j]==-1)
            sum++;
    }
    return sum;
}
void dfs(int x,int y,int s){
    if(s>=n*n){
        find=1;
        return;
    }
    int i,j,k;
    int o[8];
    for(k=0;k<8;k++){
        rem[k]=test(x+dx[k],y+dy[k],1);
        o[k]=k;
    }
    for(i=0;i<8;i++)
        for(j=1;j<8;j++)
            if(rem[o[j]]<rem[o[j-1]])
                tmp=o[j],o[j]=o[j-1],o[j-1]=tmp;
    for(k=0;k<8;k++){
        i=x+dx[o[k]],j=y+dy[o[k]];
        if(i>=0 && j>=0 && i<n && j<n && map[i][j]==-1){
            map[i][j]=s+1;
            dfs(i,j,s+1);
            if(find)return;
            map[i][j]=-1;
        }
    }
}
main(){
int i,j,x,y;
while(scanf("%d %d %d",&n,&x,&y)!=EOF){
    find=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            map[i][j]=-1;
    x--,y--;
    map[x][y]=1;
    dfs(x,y,1);
    if(!find){
        puts("No Circuit Tour.");
        continue;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%5d",map[i][j]);
        puts("");
    }
}
}
