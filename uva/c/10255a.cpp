#include<stdio.h>
int n,t,cut,find,map[50][50],tour[51][50][50],
    dx[]={-2,-1,1,2,2,1,-1,-2},
    dy[]={1,2,2,1,-1,-2,-2,-1},
    sx[]={0,0,0,0,0,1,1,1,1,1,1,1,2,4,2,6,1,4,2,1,1,4},
    sy[]={1,1,2,1,3,2,1,2,6,2,6,5,4,5,2,1,4,1,4,5,0,5};
int calc(int x,int y){
    int i,j,k,s=0;
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];
        if(x>=0 && y>=0 && x<n && y<n && map[i][j]<0)s++;
    }
    return s-1;
}
void go(int x,int y,int s){
    if(cut--<0)return;
    int i,j,k,p[8],q[8];
    if(find)return;
    if(s>=n*n){
        map[x][y]=s;
        for(k=0;k<8;k++){
            i=x+dx[k],j=y+dy[k];
            if(map[i][j]==1)
                find=1;
        }
        if(!find)map[x][y]=-1;
        return;
    }
    for(k=0;k<8;k++){
        p[k]=20,q[k]=k;
        i=x+dx[k],j=y+dy[k];
        if(i<0 || j<0 || i>=n || j>=n || map[i][j]>=0)
            continue;
        p[k]=calc(i,j);
    }
    for(i=0;i<8;i++)
        for(j=1;j<8;j++)
            if(p[q[j]]<p[q[j-1]])
                t=q[j],q[j]=q[j-1],q[j-1]=t;
    map[x][y]=s;
    for(i=0;i<8 && p[q[i]]<20 && (!i || p[q[i]]==p[q[i-1]]);i++)
        go(x+dx[q[i]],y+dy[q[i]],s+1);
    if(!find)map[x][y]=-1;
}
main(){
int i,j,k,x,y,f;
for(n=6,k=0;n<50;n++,n++,k++){
    find=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            map[i][j]=-1;
    /*for(i=0;i<n && !find;i++)
        for(j=0;j<n && !find;j++){*/
    cut=5000;
    go(sx[k],sy[k],1);
            /*if(find)
                printf("%d %d %d\n",n,i,j);
        }*/
    if(!find)
        printf("Failed at %d\n",n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            tour[n][i][j]=map[i][j];
}
while(scanf("%d %d %d",&n,&x,&y)!=EOF){
    if(f)puts("");
    else f=1;
    if(n==1){
        puts("    1");
        continue;
    }
    if(n&1 || n<6){
        puts("No Circuit Tour.");
        continue;
    }
    x--,y--;
    k=tour[n][x][y];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%5d",(tour[n][i][j]-k+n*n)%(n*n)+1);
        puts("");
    }
}
}
