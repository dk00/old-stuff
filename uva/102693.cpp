/*
Solution:
    1.Calculate all pair path through Villages.
      Super-run never through a Castle,so when arrival a castle,
      we should stop.
    2.To determinate minimal time to go home with n super-run,
      we can use minimal time with n-1 super run to do it.
*/
#include<stdio.h>
main(){
scanf("%d",&t);
while(t--){
    scanf("%d %d %d %d %d",&a,&b,&m,&l,&n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            c[i][j]=200000000;
            d[i][j]=0;
        }
        for(j=0;j<n;j++)to[j][i]=-1;
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
    for(i=1;i<a+b;i++){
        if(d[0][i])to[0][i]=d[0][i];
        if(c[0][i])to[1][i]=0;
    }
    for(l=0;l<=n;l++){
        while(1){
            for(i=0;i<a+b && to[i]<0;i++)
            if(i>=a+b)break;
            for(j=i+1;j<a+b;j++)
                if(to[j]<to[i])i=j;
            for(j=0;j<a+b;j++){
                to[j]<?=(to[i]+d[i][j]);
                if(c[i][j])to[l+1][j]<?=to[i]
            }
            to[i]=-1;
        }
    }
    printf("%d\n",to[n][a+b-1]);
}
}
