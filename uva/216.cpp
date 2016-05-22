#include<stdio.h>
#include<math.h>
int linked[8],path[8],best[8],n,x[8],y[8];
double min,len,dist[8][8];
void dfs(int d){
    int i;
    if(d>=n){
        for(i=1,len=0;i<n;i++) len+=dist[path[i-1]][path[i]]+16.0;
        if(len<min){
            for(i=0;i<n;i++) best[i]=path[i];
            min=len;
        }
        return;
    }
    for(i=0;i<n;i++){
        if(!linked[i]){
            linked[i]=1;
            path[d]=i;
            dfs(d+1);
            linked[i]=0;
        }
    }
    return;
}
main(){
int i,j,network=1;
for(;1;network++){
    scanf("%d",&n);
    if(n<=0) break;
    for(i=0;i<n;i++) scanf("%d %d",&x[i],&y[i]);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                dist[i][j]=0;
                continue;
            }
            dist[i][j]=pow(pow(x[i]-x[j],2)+pow(y[i]-y[j],2),0.5);
        }
    }min=30000.0;
    dfs(0);
    printf("*****************************");
    printf("*****************************");
    printf("\nNetwork #%d\n",network);
    for(i=1;i<n;i++){
        printf("Cable requirement to connect (%d,%d) to (%d,%d)"
        ,x[best[i-1]],y[best[i-1]],x[best[i]],y[best[i]]);
        printf(" is %.2lf feet.\n",dist[best[i-1]][best[i]]+16.0);
    }
    printf("Number of feet of cable required is %.2lf.\n",min);
}
}
