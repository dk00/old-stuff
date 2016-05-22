#include<stdio.h>
#include<stdlib.h>
struct qqq{
    int node;
    qqq *next;
};
main(){
int i,j,k,n,link[31][31],node[31],l1,l2,tl[31],Case=1,ttl;
qqq *now,*top,*start;
start=(qqq *)malloc(sizeof(qqq));
start->next=(qqq *)malloc(sizeof(qqq));
start->next->next=start;
while(1){
    scanf("%d",&n);
    if(n<=0) break;
    for(i=0;i<31;i++) node[31]=0;
    for(i=0;i<n;i++){
        scanf("%d %d",&l1,&l2);
        for(j=0;node[j]!=l1;j++);
        for(k=0;node[k]!=l2;k++);
        node[j]=l1;
        node[k]=l2;
        link[l1][l2]=1;
        link[l2][l1]=1;
    }
    for(n=0;node[n]==0;n++);
    for(;;Case++){
        now=start;
        top=now->next;
        k=n-1;
        for(i=0;i<31;i++) tl[i]=-1;
        scanf("%d",&l1);
        if(l1<=0) break;
        for(j=0;node[j]!=l1;j++);
        now->node=j;
        scanf("%d",&tl[now->node]);
    }
}
}
