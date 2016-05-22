/*
ID: s0000151
PROG: race3
LANG: C++
*/
#include<stdio.h>
int n,link[50][50],vis[50],av[50],spl[50];
void go(int p){
    if(vis[p]++)return;
    for(int i=0;i<n;i++)
        if(link[p][i])
            go(i);
}
int gos(int p){
    if(vis[p]<0)return 0;
    if(vis[p]++)return 1;
    for(int i=0;i<n;i++)
        if(link[p][i])
            if(!gos(i))return 0;
    return 1;
}
main(){
freopen("race3.in","r",stdin);
freopen("race3.out","w",stdout);
int i,j,k,avd,sp,issp;
scanf("%d",&i);
for(avd=sp=n=0;i!=-1;n++){
    link[n][i]=1;
    while(i!=-2){
        link[n][i]=1;
        scanf("%d",&i);
    }
    scanf("%d",&i);
}
for(k=1;k<n-1;k++){
    for(i=0;i<n;i++)vis[i]=0;
    vis[k]=1;
    go(0);
    if(!vis[n-1]){
        avd++;
        issp=av[k]=1;
        for(i=0;i<n;i++)if(vis[i])vis[i]=-1;
        vis[k]=0;
        if(gos(k)){
            sp++;
            spl[k]=1;
        }
    }
}
printf("%d",avd);
for(i=1;i<n-1;i++)
    if(av[i])printf(" %d",i);
printf("\n%d",sp);
for(i=1;i<n-1;i++)
    if(spl[i])printf(" %d",i);
puts("");
}
