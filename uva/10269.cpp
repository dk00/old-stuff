/*
Solution:
    1.Calculate all pair path through Villages.
      Super-run never through a Castle,so when arrival a castle,
      we should stop.
    2.To determinate minimal time to go home with n super-run,
      we can use minimal time with n-1 super run to do it.
*/
int c[100][100],d[100][100],to[12][100],p[12][100];
#include<stdio.h>
main(){
int i,j,k,l,m,n,t,a,b;
scanf("%d",&t);
while(t--){
    scanf("%d %d %d %d %d",&a,&b,&m,&l,&n);
    for(i=0;i<a+b;i++){
        for(j=0;j<a+b;j++){
            c[i][j]=200000000;
            d[i][j]=0;
        }
        for(j=0;j<n;j++)p[j][i]=i;
    }
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]=c[j][i]=d[i][j]=d[j][i]=k;
    }
    for(k=0;k<a;k++)
        for(i=0;i<a+b;i++)
            for(j=0;j<a+b;j++)
                c[i][j]<?=(c[i][k]+c[k][j]);
    for(i=0;i<a+b;i++)
        for(j=0;j<a+b;j++)
            if(c[i][j]>l)c[i][j]=0;
    to[0][0]=0;
    p[0][0]=1;
    for(l=0;l<=n;l++){
        while(1){
            for(i=0;i<a+b && (p[l][i]<0 || p[l][i]==i);i++);
            if(i>=a+b)break;
            for(j=i+1;j<a+b;j++)
                if(p[l][j]>=0 && p[l][j]!=j && to[l][j]<to[l][i])i=j;
            for(j=0;j<a+b;j++){
                if(p[l][j]<0)continue;
                if(d[i][j] && (to[l][i]+d[i][j]<to[l][j] || p[l][j]==j)){
                    to[l][j]=(to[l][i]+d[i][j]);
                    p[l][j]=i;
                }
                if(c[i][j] && (to[l][i]<to[l+1][j] || p[l+1][j]==j)){
                    to[l+1][j]=to[l][i];
                    p[l+1][j]=i;
                }
            }
            p[l][i]=-1;
        }
    }
    printf("%d\n",to[n][a+b-1]);
}
}
