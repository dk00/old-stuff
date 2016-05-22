#include<stdio.h>
const int inf=2147483647;
struct pos{
    int x,y;
    int get(){
        scanf("%d %d",&x,&y);
        return x--|--y;
    }
}gold,soldier[200],target[200];
int n,m,k,t,magic,map[100][100],num[200];
int rem,cost[200][200],tmp[100][100];
void go(int x,int y,int s,int dir){
    if(s>=tmp[x][y])return;
    if(tmp[x][y]==inf)rem--;
    tmp[x][y]<?=s;
    if(x && map[x-1][y]*dir>=map[x][y]*dir && tmp[x-1][y]>s)
        go(x-1,y,s,dir);
    if(y && map[x][y-1]*dir>=map[x][y]*dir && tmp[x][y-1]>s)
        go(x,y-1,s,dir);
    if(x+1<n && map[x+1][y]*dir>=map[x][y]*dir && tmp[x+1][y]>s)
        go(x+1,y,s,dir);
    if(y+1<m && map[x][y+1]*dir>=map[x][y]*dir && tmp[x][y+1]>s)
        go(x,y+1,s,dir);
}
void calc(int x,int y,int dir){
int i,j,step;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            tmp[i][j]=inf;
    tmp[x][y]=0;
    rem=n*m-1;
    go(x,y,0,dir);
    for(dir=-dir,step=1;rem>0;dir=-dir,step++)
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                if(tmp[i][j]==step-1){
                    if(i && tmp[i-1][j]>step)go(i-1,j,step,dir);
                    if(j && tmp[i][j-1]>step)go(i,j-1,step,dir);
                    if(i+1<n && tmp[i+1][j]>step)go(i+1,j,step,dir);
                    if(j+1<m && tmp[i][j+1]>step)go(i,j+1,step,dir);
                }
}
int nn,c[500][500],p[500];
int findpath(int v){
    p[v]=1;
    if(v==nn-1)return 1;
    for(int i=1;i<nn;i++)
        if(!p[i] && c[v][i]){
            c[v][i]--;
            if(findpath(i)){
                c[i][v]++;
                return 1;
            }
            c[v][i]++;
        }
    return 0;
}
int flow(){
int i,j;
    nn=2*k+t+2;
    for(i=0;i<nn;i++)
        for(j=0;j<nn;j++)c[i][j]=0;
    for(i=2*k;i>0;i--)c[0][i]=1;
    for(i=0;i<t;i++)c[2*k+i+1][nn-1]=num[i];
    for(i=0;i<2*k;i++)
        for(j=0;j<t;j++)c[i+1][j+2*k+1]=(cost[i][j]<=magic);
    for(i=0;;i++){
        for(j=0;j<nn;j++)p[j]=0;
        if(!findpath(0))break;
    }
    return i;
}
main(){
int i,j,f,tt,find;
freopen("10418.in","r",stdin);
freopen("10418.out","w",stdout);
scanf("%d",&tt);
while(tt--){
    scanf("%d %d %d %d",&n,&m,&k,&t);
    for(i=0;i<k;i++)soldier[i].get();
    for(i=0;i<k;i++)soldier[i+k].get();
    gold.get();
    for(i=0;i<t;i++){
        target[i].get();
        scanf("%d",&num[i]);
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)scanf("%d",&map[i][j]);
    for(i=0;i<k;i++){
        calc(soldier[i].x,soldier[i].y,1);
        for(j=0;j<t;j++)
            cost[i][j]=tmp[target[j].x][target[j].y];
    }
    for(i=0;i<k;i++){
        calc(soldier[i+k].x,soldier[i].y,-1);
        for(j=0;j<t;j++)
            cost[i+k][j]=tmp[target[j].x][target[j].y];
    }
    for(magic=0;;magic++){
        f=flow();
        if(f+magic>=2*k)break;
    }
    printf("%d\n",magic);
}
}
