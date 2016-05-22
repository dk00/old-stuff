/*
ID: s0000151
PROG: ditch
LANG: C++
*/
#include<stdio.h>
#define MAXV 300
#define Min(a,b) (a)<(b)?(a):(b)
int s,t,n,rep,pup,c[MAXV][MAXV],e[MAXV],h[MAXV],rel[MAXV],pus[MAXV][2];
void relabel(int p){
    int i,j,min=n;
    for(i=0;i<n;i++)
        if(c[p][i]){
            if(h[i]+1<min){
                j=0;
                min=h[i]+1;
            }
            if(h[i]+1==min){
                pus[pup+j][0]=p;
                pus[pup+j++][1]=i;
            }
        }
    pup+=j;
	h[p]=min;
}
void push(int p1,int p2){
    if(h[p1]+1!=h[p2])return;
    int f=Min(c[p1][p2],e[p1]);
    c[p1][p2]-=f;
    c[p2][p1]+=f;
	e[p1]-=f;
    e[p2]+=f;
    if(f && p2!=t && p2!=s)rel[rep++]=p2;
}
int flow(){
    int i,j,max;
    h[s]=n;
    for(max=pup=rep=i=0;i<n;i++){
        if(i==s || !c[s][i])continue;
        e[i]+=c[s][i];
        c[i][s]+=c[s][i];
        c[s][i]=0;
        if(i!=t)rel[rep++]=i;
    }
    while(rep+pup){
        while(rep)
            relabel(rel[--rep]);
        while(pup)
            push(pus[pup][0],pus[--pup][1]);
    }
    return e[t];
}
main(){
int i,j,k,m;
freopen("ditch.in","r",stdin);
freopen("ditch.out","w",stdout);
scanf("%d %d",&m,&n);
    for(i=0;i<n;i++){
        h[i]=e[i]=0;
        for(j=0;j<n;j++)c[i][j]=0;
    }
	t=n-1;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        c[i-1][j-1]+=k;
    }
    printf("%d\n",flow());
}
