#include<stdio.h>
#include<stdlib.h>
struct linkedlist{
    int link;
    linkedlist *next;
}list[30001];
int done[30001],p[30001];
long k,n;
void dfs(int who){
    done[who]=1;
    k++;
    for(int i=1;i<=n;i++)if(!done[i])dfs(i);
}
main(){
long t,m,i,j;
scanf("%ld",&t);
while(t--){
    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++)link[i][j]=0;
        done[i]=0;
    }
    while(m--){
        scanf("%ld %ld",&i,&j);
    }
    for(i=1;i<=n;i++){
        if(!done[i]){
            k=0;
            dfs(i);
            m>?=k;
        }
    }
    printf("%ld\n",m);
}
}
