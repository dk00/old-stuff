/*
ID: s0000151
PROG: agrinet
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
struct edge{
    int x;
    int y;
    int len;
};
edge heap[5060];
int size=1,i,j,s,t;
void swip(int a,int b){
    t=heap[a].x;heap[a].x=heap[b].x;heap[b].x=t;
    t=heap[a].y;heap[a].y=heap[b].y;heap[b].y=t;
    t=heap[a].len;heap[a].len=heap[b].len;heap[b].len=t;
}
void in(){
    heap[size].x=i;
    heap[size].y=j;
    heap[size].len=s;
    adjust(size++);
}
void popmin(){
    swip(0,--size);
    adjust(0);
}
void adjust(int p){
    if(p*2<size && heap[p].len>heap[p*2].len){          //L
        swip(p,p*2);
        adjust(p*2);
    }
    else if(p*2+1<size && heap[p].len>heap[p*2+1].len){ //R
        swip(p,p*2+1);
        adjust(p*2+1);
    }
    else if(p>0 && heap[p].len<heap[p/2].len){          //P
        swip(p,p/2);
        adjust(p/2);
    }
}
main(){
if(!DEBUG){freopen("agrinet.in","r",stdin);
freopen("agrinet.out","w",stdout);}
int n,done[101],k,sum=0;
scanf("%d",&n);
for(i=0;i<n;i++){
    done[i]=0;
    for(j=0;j<=i;j++){
        scanf("%d",&s);
        in();
    }
    for(j=i+1;j<n;j++)scanf("%d",&s);
}
for(n--){
    
    
    
}
if(DEBUG)scanf(" ");
}
