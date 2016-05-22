/*
ID: s0000151
PROG: butter
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
struct edge{
    int v,c;
    edge *next;
}*ptr,*path[800],*top[800];
int p2[800][800],cow[800],to[800];
main(){
int i,j,k,l,n,p,c,min,cost;
freopen("butter.in","r",stdin);
freopen("butter.out","w",stdout);
scanf("%d %d %d",&n,&p,&c);
for(i=0;i<p;i++)top[i]=path[i]=NULL;
while(n--){
    scanf("%d",&i);
    cow[--i]++;
}
while(c--){
    scanf("%d %d %d",&i,&j,&k);
    i--,j--;
    if(top[i]==NULL){
        top[i]=(edge *)malloc(sizeof(edge));
        top[i]->next=NULL;
    }
    if(top[j]==NULL){
        top[j]=(edge *)malloc(sizeof(edge));
        top[j]->next=NULL;
    }
    top[i]->v=j,top[i]->c=k,top[i]->next=(edge *)malloc(sizeof(edge));
    top[j]->v=i,top[j]->c=k,top[j]->next=(edge *)malloc(sizeof(edge));
    top[i]=top[i]->next;
    top[j]=top[j]->next;
    top[i]->next=top[j]->next=NULL;
    min+=k;
}
for(i=0;i<p;i++){    //run dijkstra here
    if(!cow[i])continue;
    for(k=0;k<p;k++)
        to[k]=199999999;
    for(ptr=path[i];ptr!=NULL;ptr=ptr->next)
        to[ptr->v]=ptr->c;
    for(j=p-1;j--;){
        for(k=0;!to[k];k++);
        for(l=k+1;l<p;l++)
            if(to[l] && to[l]<to[k])k=l;
        p2[i][k]=to[k];
        for(ptr=path[k];ptr!=NULL;ptr=ptr->next)
            to[ptr->v]<?=(to[k]+ptr->c);
        to[k]=0;
    }
    p2[i][i]=0;
}
for(i=0;i<p;i++){
    for(cost=j=0;j<p;j++){
        if(!cow[j])continue;
        cost+=p2[j][i]*cow[j];
    }
    min<?=cost;
}
printf("%d\n",min);
}
