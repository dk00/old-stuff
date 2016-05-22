#include<stdio.h>
main(){
int order[101][101];
int n,m,s,i,j,task[101];
while(scanf("%d %d",&n,&m)){
    if(!n && !m)break;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)order[i][j]=0;
        task[i]=0;
    }
    while(m-- && scanf("%d %d",&i,&j)){
        task[j-1]++;
        order[i-1][j-1]=1;
    }
    for(s=n;s--;task[i]-=1){
        for(i=0;i<n && task[i];i++);
        printf("%d",i+1);
        for(j=0;j<n;j++)task[j]-=order[i][j];
        if(s)printf(" ");
        else puts(" ");
    }
}
}
