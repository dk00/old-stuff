#include<stdio.h>
#include<stdlib.h>
struct pos{
    int x,y;
    void get(){scanf("%d %d",&x,&y);x--,y--;}
}r[120],g[120],u,ta[250];
struct Q{
    int x,y,s,d;
}q1[100000],q2[100000];
int n,m,num,max,map[100][100],tmp[100][100];
void go(int to[100][100],int x,int y,int d){
int i1,i2,j1,j2,s;
    for(i1=0;i1<n;i1++)
        for(j1=0;j1<m;j1++)
            tmp[i1][j1]=1;
    q1[0].x=x,q1[0].y=y,q1[0].d=d,q1[0].s=0;
    for(i1=i2=j2=0,j1=1;i1<j1 || i2<j2;){
        if(i1<j1){
            x=q1[i1].x,y=q1[i1].y,d=q1[i1].d,s=q1[i1].s;
            i1++;
        }
        else if(i2<j2){
            x=q2[i2].x,y=q2[i2].y,d=q2[i2].d,s=q2[i2].s;
            i2++;
        }
        if(s>=to[x][y] || !tmp[x][y])continue;
        to[x][y]<?=s;
        if(x && tmp[x-1][y]){
            if(map[x][y]*d<=map[x-1][y]*d)
                q1[j1++]=(Q){x-1,y,s,d};
            else q2[j2++]=(Q){x-1,y,s+1,-d};
        }
        if(y && tmp[x][y-1]){
            if(map[x][y]*d<=map[x][y-1]*d)
                q1[j1++]=(Q){x,y-1,s,d};
            else q2[j2++]=(Q){x,y-1,s+1,-d};
        }
        if(x+1<n && tmp[x+1][y]){
            if(map[x][y]*d<=map[x+1][y]*d)
                q1[j1++]=(Q){x+1,y,s,d};
            else q2[j2++]=(Q){x+1,y,s+1,-d};
        }
        if(y+1<m && tmp[x][y+1]){
            if(map[x][y]*d<=map[x][y+1]*d)
                q1[j1++]=(Q){x,y+1,s,d};
            else q2[j2++]=(Q){x,y+1,s+1,-d};
        }
    }
}
int sink,use[300],o[300][300],c[300][300],step[100][100][100];
int findpath(int v){
    use[v]=0;
    if(v==sink)return 1;
    for(int i=1;i<=sink;i++)
        if(use[i] && c[v][i]){
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
int i,j,f=0;
    while(1){
        for(i=0;i<=sink;i++)use[i]=1;
        if(findpath(0))f++;
        else return f;
    }
    return 0;
}
main(){
int i,j,k,t,p,tt,find,magic,cn[200];
scanf("%d",&tt);
while(tt--){
    scanf("%d %d %d %d",&n,&m,&k,&t);
    if(k>50)puts("error");
    for(i=0;i<k;i++)r[i].get();
    for(i=0;i<k;i++)g[i].get();
    u.get();
    for(i=0;i<t;i++){
        ta[i].get();
        scanf("%d",&cn[i]);
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            scanf("%d",&map[i][j]);
            for(p=0;p<k*2;p++)
                step[p][i][j]=100000;
        }
    for(i=0;i<k;i++){
        go(step[i],r[i].x,r[i].y,1);
        go(step[k+i],g[i].x,g[i].y,-1);
    }
    for(magic=0;magic<2*k;magic++){
        for(i=0;i<=sink;i++)
            for(j=0;j<=sink;j++)
                c[i][j]=o[i][j];
        for(i=0;i<k;i++)
            for(j=0;j<t;j++){
                if(step[i][ta[j].x][ta[j].y]<=magic)
                    c[i+1][2*k+t+1]=1;
                if(step[k+1][ta[j].x][ta[j].y]<=magic);
                    c[i+k+1][2*k+t+1]=1;
            }
        if(flow()+magic>=2*k)break;
    }
    printf("%d\n",magic);
}
}
