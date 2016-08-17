#include<stdio.h>
#include<stdlib.h>
struct edge{
    int x,y;
    long dis;
}e[602501];
int set[750],dep[750];
int numcmp(const void *a,const void *b){
return ((edge *)a)->dis-((edge *)b)->dis;
}
int sunion(int i,int j){
    while(set[i]!=i)i=set[i];
    while(set[j]!=j)j=set[j];
    if(i==j)return 0;
    if(dep[i]>dep[j]){
        set[j]=i;
        dep[i]=dep[j]+1;
    }
    else{
        set[i]=j;
        dep[j]=dep[i]+1;
    }
    return 1;
}
main(){
int i,j,k,ne,nu,n,m,t,x[750],y[750],u[750];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        set[i]=i;
        dep[i]=0;
    }
    for(k=n-1,ne=i=0;i<n;i++){
        scanf("%d %d",&x[i],&y[i]);
        for(j=0;j<i;j++){
            e[ne].x=i;
            e[ne].y=j;
            e[ne++].dis=
            (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
        }
    }
    qsort(e,ne,sizeof(e[0]),numcmp);
    scanf("%d",&m);
    while(m--){
        scanf("%d %d",&i,&j);
        if(sunion(--i,--j))k--;
    }
    for(nu=i=0;k && i<ne;i++)
        if(sunion(e[i].x,e[i].y)){
            u[nu++]=i;
            k--;
        }
    if(!nu){
        puts("No new highways need");
        continue;
    }
    for(i=0;i<nu;i++)
        printf("%d %d\n",e[u[i]].y+1,e[u[i]].x+1);
}
}
