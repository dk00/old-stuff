#include<stdio.h>
#include<stdlib.h>
#include"Fheap.h"
int n,t,s,c[50][50],px[50],py[50];
int hope(int able,int v1,int v2){
    int x1=px[v1]<?px[v2],
        y1=py[v1]<?py[v2],
        x2=px[v1]>?px[v2],
        y2=py[v1]>?py[v2];
    for(int i=1;i<=t;i++){
        if(i!=v1 && i!=v2 && able&(1<<i) && x1<px[i] && px[i]<x2 &&
        y1<py[i] && px[i]<y2)return 0;
    }
    return 1;
}
main(){
int i,j,C=1;
px[0]=py[0]=0;
while(scanf("%d %d %d",&n,&t,&s) && n+t+s){
    Fheap heap;
    heap.n=0;
    heap.min=NULL;
    for(i=1;i<=t;i++)
        scanf("%d %d",&px[i],&py[i]);
    px[t+1]=py[t+1]=n-1;
    for(i=0;i<=t+1;i++)
        for(j=0;j<=t+1;j++)
            c[i][j]=abs(px[i]-px[j])+abs(py[i]-py[j]);
    heap.insert(0,0,0,~1);
    while(1){
        now=heap.extractmin();
        if(now.q==s)
            heap.insert(now.n+c[now.v][t+1],t+1,now.q,0);
        if(now.v==t+1)break;
        for(i=1;i<=t;i++){
            if(now.able&(1<<i) && hope(now.able,now.v,i))
                heap.insert(now.n+c[now.v][i],i,now.q+1,now.able&~(1<<i));
        }
    }
    printf("Case %d: %d\n",C++,now.n);
}
}
