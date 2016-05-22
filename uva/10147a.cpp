#include<stdio.h>
#include<math.h>
double sum,dis[750][750],to[750];
main(){
int i,j,k,n,m,t,x[750],y[750],par[750],l[750][2];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d %d",&x[i],&y[i]);
        for(j=0;j<i;j++)
            dis[i][j]=dis[j][i]=
            sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
        dis[i][i]=0.0;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d %d",&i,&j);
        dis[i-1][j-1]=dis[j-1][i-1]=0.0;
    }
    for(sum=k=i=0;i<n;i++){
        par[i]=0;
        to[i]=dis[0][i];
    }
    par[0]=-1;
    for(m=n-1;m--;){
        for(i=0;par[i]<0;i++);
        for(j=i+1;j<n;j++)
            if(par[j]>=0 && to[i]>to[j])i=j;
        if(to[i]>0.0){
            l[k][1]=par[i];
            l[k++][0]=i;
            sum+=to[i];
        }
        par[i]=-1;
        for(j=0;j<n;j++)
            if(par[j]>=0 && dis[i][j]<to[j]){
                par[j]=i;
                to[j]=dis[i][j];
            }
    }
    if(sum==0.0){
        puts("No new highways need");
        continue;
    }
    for(i=0;i<k;i++)
        printf("%d %d\n",l[i][0]+1,l[i][1]+1);
}
}
