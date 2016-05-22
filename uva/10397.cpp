#include<stdio.h>
#include<math.h>
main(){
int par[750],i,j,x[750],y[750],n,m,done[750];
int s1,min;
double linked[750],dist[75][75],len,sum;
while(scanf("%d",&n)!=EOF){
    for(i=0;i<n;i++){
        scanf("%d %d",&x[i],&y[i]);
        x[i]+=10000;y[i]+=10000;
    }
    for(i=0;i<n;i++){
        linked[i]=999999;par[i]=-1;done[i]=0;
        for(j=0;j<n;j++){
            dist[i][j]=pow(pow(x[i]-x[j],2)+pow(y[i]-y[j],2),0.5);
        }
    }
    scanf("%d",&m);
    for(i=0;i<m;i++){
        scanf("%d %d",&x[0],&y[0]);
        dist[x[0]-1][y[0]-1]=0;
        dist[y[0]-1][x[0]-1]=0;
    }
    done[0]=1;
    for(i=0;i<n;i++){
        par[i]=0;
        linked[i]=dist[0][i];
    }
    while(1){
        for(i=0;i<n && done[i];i++);
        if(i>=n) break;
        for(min=i;i<n;i++){
            if(linked[i]<linked[min] && !done[i])
                min=i;
        }
        for(i=0;i<n;i++){
            if(i==min)continue;
            if(!done[i] && linked[i]>dist[min][i]){
                par[i]=min;
                linked[i]=dist[min][i];
            }
        }
        done[min]=1;
    }
    for(i=0,sum=0;i<n;i++) sum+=linked[i];
    printf("%.2lf\n",sum);
}
}
