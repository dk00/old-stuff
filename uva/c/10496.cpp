#include<stdio.h>
int k,min,picked[11],dist[11][11];
int abs(int n){
    return n>?-n;
}
void dfs(int p,int len,int d){
    if(d>=k){
        min<?=(len+dist[p][0]);
        return;
    }
    for(int i=1;i<=k;i++)
        if(!picked[i]){
            picked[i]=1;
            dfs(i,len+dist[p][i],d+1);
            picked[i]=0;
        }
}
main(){
int t,m,n,x[11],y[11];
scanf("%d",&t);
while(t--){
    scanf("%d %d %d %d %d",&m,&n,&x[0],&y[0],&k);
    for(m=1;m<=k;m++)
        scanf("%d %d",&x[m],&y[m]);
    for(m=0;m<=k;m++)
        for(n=0;n<=k;n++)
            dist[m][n]=abs(x[m]-x[n])+abs(y[m]-y[n]);
    min=5000;
    dfs(0,0,0);
    printf("The shortest path has length %d\n",min);
}
}
