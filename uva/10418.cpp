#include<stdio.h>
struct pos{
    int x,y;
    int get(){
        scanf("%d %d",&x,&y);
        return x--+--y;
    }
}sold[100],gold,tgt[102];
int k,t,n,m,uid,p,q;
int num[102],map[100][100],tid[100][100],s_t[100][101];
int tmp[100][100],occ[100][100];
int _b[4][10000],*q1x=_b[0],*q2x=_b[1],*q1y=_b[2],*q2y=_b[3],*_tmp;
void go(int x,int y,int s,int dir){
    if(occ[x][y]==uid)return;
    tmp[x][y]=s;
    occ[x][y]=uid;
    if(x && map[x-1][y]*dir>=map[x][y]*dir && occ[x-1][y]!=uid)
        go(x-1,y,s,dir);
    if(y && map[x][y-1]*dir>=map[x][y]*dir && occ[x][y-1]!=uid)
        go(x,y-1,s,dir);
    if(x+1<n && map[x+1][y]*dir>=map[x][y]*dir && occ[x+1][y]!=uid)
        go(x+1,y,s,dir);
    if(y+1<m && map[x][y+1]*dir>=map[x][y]*dir && occ[x][y+1]!=uid)
        go(x,y+1,s,dir);
    if(x && map[x-1][y]*dir<=map[x][y]*dir && occ[x-1][y]!=uid)
        q2x[q]=x-1,q2y[q++]=y;
    if(y && map[x][y-1]*dir<=map[x][y]*dir && occ[x][y-1]!=uid)
        q2x[q]=x,q2y[q++]=y-1;
    if(x+1<n && map[x+1][y]*dir<=map[x][y]*dir && occ[x+1][y]!=uid)
        q2x[q]=x+1,q2y[q++]=y;
    if(y+1<m && map[x][y+1]*dir<=map[x][y]*dir && occ[x][y+1]!=uid)
        q2x[q]=x,q2y[q++]=y+1;
}
void calc(int x,int y,int dir){
    q1x[0]=x;
    q1y[0]=y;
    for(x=0;x<n;x++)
        for(y=0;y<m;y++)tmp[x][y]=-1;
    int s;
    for(p=1,s=q=0;p>0;p=q,q=0,dir=-dir,s++){
        while(p--){
            if(tmp[q1x[p]][q1y[p]]==-1)
                go(q1x[p],q1y[p],s,dir);
        }
        _tmp=q1x;q1x=q2x;q2x=_tmp;
        _tmp=q1y;q1y=q2y;q2y=_tmp;
    }
}
int magic,nn,c[205][205],u[205];
int findpath(int v){
    if(v==nn-1)return 1;
    u[v]=uid;
    for(int i=1;i<nn;i++)
        if(u[i]!=uid && c[v][i]){
            c[v][i]--;
            if(findpath(i)){
                c[i][v]++;
                return 1;
            }
            c[v][i]++;
        }
    return 0;
}
int flow(int n){
int i,j;
    nn=k*2+t+2;
    for(i=0;i<nn;i++)
        for(j=0;j<nn;j++)c[i][j]=0;
    for(i=1;i<=2*k;i++){
        c[0][i]=1;
        for(j=1;j<=t;j++)
            c[i][2*k+j]=(s_t[i-1][j-1]<=magic);
    }
    for(j=0;j<t;j++)c[2*k+j+1][nn-1]=num[j];
    for(uid++,i=0;i<2*k;i++,uid++)
        if(!findpath(0))break;
    return i;
}
main(){
int i,j,f,tt,find;
uid=1;
scanf("%d",&tt);
while(tt--){
    scanf("%d %d %d %d",&n,&m,&k,&t);
    for(i=0;i<2*k;i++)sold[i].get();
    gold.get();
    for(i=0;i<t;i++){
        tgt[i].get();
        scanf("%d",&num[i]);
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)scanf("%d",&map[i][j]);
    for(i=0,uid++;i<k;i++,uid++){
        calc(sold[i].x,sold[i].y,1);
        for(j=0;j<t;j++)s_t[i][j]=tmp[tgt[j].x][tgt[j].y];
    }
    for(i=0,uid++;i<k;i++,uid++){
        calc(sold[i+k].x,sold[i+k].y,-1);
        for(j=0;j<t;j++)s_t[i][j]=tmp[tgt[j].x][tgt[j].y];
    }
    for(magic=0;;magic++){
        f=flow(1);
        if(f>=2*k)
            break;
    }
    printf("%d\n",magic);
}
}
