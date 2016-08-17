#include<stdio.h>
#include<math.h>
double link[1000][1000],to[1000],sum;
int done[1000];
main(){
int n,m,i,j,t,w,x[10000],y[10000];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d %d",&x[i],&y[i]);
        for(j=0;j<i;j++)link[i][j]=link[j][i]=
        sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d %d",&i,&j);
        link[i-1][j-1]=link[j-1][i-1]=0;
    }
    for(m=n-1,sum=w=i=0;i<n;i++){to[i]=link[0][i];done[i]=1;}
    done[w=0]=0;
    while(m--){
        for(i=0;!done[i];i++);
        for(j=i+1;j<n;j++)if(done[j] && to[j]<to[i])i=j;
        if(to[i])sum=1;
        if(to[i]>0){x[w]=done[i];y[w++]=i+1;}
        done[i]=0;
        for(j=0;j<n;j++){
            if(done[j] && to[j]>link[i][j]){
                done[j]=i+1;
                to[j]=link[i][j];
            }
        }
    }
    if(sum<1){puts("No new highways need");continue;}
    for(i=0;i<w;i++)printf("%d %d\n",y[i],x[i]);
    if(t)puts("");
}
}
