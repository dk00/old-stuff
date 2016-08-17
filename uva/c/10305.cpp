#include<stdio.h>
main(){
short order[102][102],task[102],i,j,n,m,s;
while(scanf("%d %d",&n,&m)){
    if(!(s=n) && !m)break;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++)order[i][j]=0;
        task[i]=0;
    }
    while(m--){
        scanf("%d %d",&i,&j);
        order[i][j]=1;
        task[j]++;
    }
    while(s--){
        for(i=1;i<=n && !task[i];i++);
        printf("%d",i);
        if(n)printf(" ");
        else puts("");
        for(task[i]=0,j=1;j<=n;j++)task[j]+=order[i][j];
    }
}
}
