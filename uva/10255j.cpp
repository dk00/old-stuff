#include<stdio.h>
int n,y,map[50][50],
    dx[]={1,2,1,2,-1,-2,-1,-2},
    dy[]={2,1,-2,-1,2,1,-2,-1};
int test(int x,int y,int s){
    int i,j,k;
    if(s>=n*n){
        for(k=0;k<8;k++){
            i=x+dx[k],j=y+dy[k];
            if(i>=0 && i<n && j>=0 && j<n && map[i][j]==1)
                return 1;
        }
        return 0;
    }
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];
        if(i>=0 && i<n && j>=0 && j<n)
            if(test(i,j,s+1))
                return 1;
    }
    return 0;
}
main(){
int i,j,x,y,t=1;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            scanf("%d",&map[i][j]);
            if(map[i][j]==1)
                x=i,y=j;
        }
    printf("test %d",t++);
    if(test(x,y,1))puts(" OK");
    else puts("Failed");
}
}
