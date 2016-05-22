#include<stdio.h>
int n,num,max,u[100],v[100],best[100],c[100][100];
void inline go(int d,int i){
    if(i>=n)return;
    for(;i<n && u[i]<1;i++);
    if(i<n){
        num++,v[i]=1,u[i]--;
        int j;
        if(num>max){
            max=num;
            for(j=0;j<n;j++)best[j]=v[j];
        }
        for(j=i+1;j<n;j++)
            if(c[i][j])u[j]--;
        go(d+1,i+1);
        for(j=i+1;j<n;j++)
            if(c[i][j])u[j]++;
        u[i]++,v[i]=0,num--;
    }
    go(d+1,i+1);
}
main(){
int i,j,m,t;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++){
        v[i]=0;
        u[i]=1;
        for(j=0;j<n;j++)c[i][j]=0;
    }
    while(m--){
        scanf("%d %d",&i,&j);
        i--,j--;
        c[i][j]=c[j][i]=1;
    }
    num=max=0;
    go(0,0);
    for(i=0;i<n && !best[i];i++);
    printf("%d\n%d",max,i+1);
    for(i++;i<n;i++)
        if(best[i])printf(" %d",i+1);
    puts("");
}
}
