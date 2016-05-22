/*
ID: s0000151
PROG: butter
LANG: C++
*/
int p2[800][800],path[800][800],pn[800],co[800][800],cow[800],to[800];
#include<stdio.h>
main(){
int i,j,k,l,n,p,c,min,cost;
freopen("butter.in","r",stdin);
freopen("butter1.out","w",stdout);
scanf("%d %d %d",&n,&p,&c);
for(i=0;i<p;i++)pn[i]=0;
while(n--){
    scanf("%d",&i);
    cow[--i]++;
}
while(c--){
    scanf("%d %d %d",&i,&j,&k);
    i--,j--;
    path[i][pn[i]]=j;
    co[i][pn[i]++]=k;
    path[j][pn[j]]=i;
    co[j][pn[j]++]=k;
    min+=k;
}
for(i=0;i<p;i++){    //run dijkstra here
    if(!cow[i])continue;
    printf("dijkstra %d:\n",i+1);
    for(k=0;k<p;k++)
        to[k]=199999999;
    for(to[i]=0,k=0;k<pn[i];k++)
        to[path[i][k]]=co[i][k];
    for(j=p-1;j--;){
        for(k=0;!to[k];k++);
        for(l=k+1;l<p;l++)
            if(to[l] && to[l]<to[k])k=l;
        printf("    min: %d (to %d)\n",to[k],k+1);
        p2[i][k]=to[k];
        for(l=0;l<pn[k];l++)
            if(to[path[k][l]]>(to[k]+co[k][l])){
                to[path[k][l]]=to[k]+co[k][l];
                printf("        ins ->%d (%d)\n",
                path[k][l],to[k]+co[k][l]);
            }
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
