/*
ID: s0000151
PROG: ditch
LANG: C++
*/
#include<stdio.h>
int i,j,m,t,find,c[200][200],use[200],take[200],to[200];
int dijkxtra(int s){
    for(take[0]=i=1;i<m;i++){
        take[i]=0;
        use[i]=s;
        to[i]=c[s][i];
    }
    while(!take[m-1]){
        for(i=1;(take[i] || !to[i]) && i<m;i++);
        if(i>=m)break;
        for(j=i+1;j<m;j++)if(!take[j] && to[j]>to[i])i=j;
        take[i]=1;
        for(j=1;j<m;j++)
            if(!take[j] && to[j]<(to[i]<?c[i][j])){
                use[j]=i;
                to[j]=(to[i]<?c[i][j]);
            }
    }
    if(to[m-1]<=0)return 0;
    take[0]=m-1;
    for(i=m-1,t=1;use[i];i=use[i],t++)take[t]=use[i];
    take[t]=0;
    return to[m-1];
}
main(){
freopen("ditch.in","r",stdin);
freopen("ditch.out","w",stdout);
int k,n,max,flow,sum=0;
scanf("%d %d",&n,&m);
while(n--){
    scanf("%d %d",&i,&j);
    scanf("%d",&flow);
    c[i-1][j-1]+=flow;
}
use[0]=1;
while(1){
    if(!(max=dijkxtra(0)))break;
    printf("1");
    for(i=t;i>0;i--){
        c[take[i]][take[i-1]]-=max;
        c[take[i-1]][take[i]]+=max;
        printf(" -> %d",take[i-1]+1);
    }
    sum+=max;
    printf(" : (%d)\n",max);
}
printf("%d\n",sum);
}
