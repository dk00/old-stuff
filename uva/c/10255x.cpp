#include<stdio.h>
int n,find,map[50][50],path[50][50],tour[51][50][50],
    dx[]={-2,-1,1,2,2,1,-1,-2},
    dy[]={1,2,2,1,-1,-2,-2,-1};
void go(int x,int y,int s){
    if(s>=n*n){
        map[x][y]=s;
        /*int i,j,k;
        for(k=0;k<8;k++){
            i=x+dx[k],j=y+dy[k];
            if(i<0 || i>=n || j<0 || j>=n)continue;
            if(map[i][j]==1)find=1;
        }*/
        find=1; //map[x][y]=0;
        return;
    }
    if(find)return;
    map[x][y]=s;
int i,j,k,m=0,min=9,tmp[8];
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];
        if(i<0 || i>=n || j<0 || j>=n || map[i][j])continue;
        path[i][j]--;
        if(path[i][j]<min){
            min=path[i][j];
            m=1;
            tmp[0]=k;
        }
        else if(path[i][j]==min)
            tmp[m++]=k;
    }
    while(m-- && !find)
        go(x+dx[tmp[m]],y+dy[tmp[m]],s+1);
    if(find)return;
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];
        if(i<0 || i>=n || j<0 || j>=n)continue;
        path[i][j]++;
    }
    map[x][y]=0;
}
main(){
int i,j,k,x,y,px,py,f=0;
for(n=6;n<51;n++,n++){
    find=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            map[i][j]=path[i][j]=0;
            for(k=0;k<8;k++){
                px=i+dx[k],py=j+dy[k];
                path[i][j]+=(px<n && px>=0 && py<n && py>=0);
            }
        }
    path[0][0]=0;
    if(n==38)go(1,1,1);
    else go(0,0,1);
    if(!find)printf("error at %d\n",n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            tour[n][i][j]=map[i][j];
}
while(scanf("%d %d %d",&n,&x,&y)!=EOF){
    find=0,x--,y--;
    if(n==1){
        puts("    1");
        if(f)puts("");else f=1;
        continue;
    }
    if(n<=5 || n%2){
        puts("No Circuit Tour.");
        if(f)puts("");else f=1;
        continue;
    }
    k=tour[n][x][y];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%5d",(tour[n][i][j]-k+n*n)%(n*n)+1);
        puts("");
    }
    //else puts("No Circuit Tour.");
    if(f)puts("");else f=1;
}
}
