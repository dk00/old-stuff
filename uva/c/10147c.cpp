#include<math.h>
#include<stdio.h>
struct pos{
    int x,y;
    void inline get(){
        scanf("%d %d",&x,&y);
    }
}v[750];
inline int Dis(pos a,pos b){
    return((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int dis[750][750],to[750];
main(){
int i,j,n,m,t,use,p[750];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        v[i].get();
        for(j=0;j<i;j++)
            dis[i][j]=dis[j][i]=Dis(v[i],v[j]);
        dis[i][i]=p[i]=0;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d %d",&i,&j);
        i--,j--;
        dis[i][j]=dis[j][i]=-1;
    }
    for(use=i=0;i<n;i++)to[i]=dis[0][i];
    to[0]=-2;
    p[0]=-1;
    while(1){
        for(i=0;i<n && to[i]<-1;i++);
        if(i>=n)break;
        for(j=i+1;j<n;j++)
            if(to[j]>-2 && to[j]<to[i])i=j;
        if(to[i]<=-1)p[i]=-1;
        else use++;
        to[i]=-2;
        for(j=0;j<n;j++)
            if(dis[i][j]<to[j]){
                p[j]=i;
                to[j]=dis[i][j];
            }
    }
    if(use){
        for(i=1;i<n;i++)
            if(p[i]>=0)printf("%d %d\n",p[i]+1,i+1);
    }
    else puts("No new highways need");
    if(t)puts("");
}
}
