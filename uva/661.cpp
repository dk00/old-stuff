#include<stdio.h>
main(){
int i,n,m,c,S=0,now,max,cost[100],open[100];
while(scanf("%d %d %d",&n,&m,&c) && n+m+c){
    for(i=0;i<n;i++){
        scanf("%d",&cost[i]);
        open[i]=0;
    }
    for(max=now=i=0;m--;){
        scanf("%d",&i);
        i--;
        if(open[i]){
            open[i]=0;
            now-=cost[i];
        }
        else{
            open[i]=1;
            now+=cost[i];
            max>?=now;
        }
    }
    if(S++)puts("");
    printf("Sequence %d\n",S);
    if(max>c)puts("Fuse was blown.");
    else{
        puts("Fuse was not blown.");
        printf("Maximal power consumption was %d amperes.\n",max);
    }
}
}
