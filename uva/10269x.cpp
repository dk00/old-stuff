#include<stdio.h>
int c[100][100],d[100][100],to[12][100],p[12][100];
main(){
int i,j,k,l,m,n,t,a,b,ss;
scanf("%d",&t);
while(t--){
    scanf("%d %d %d %d %d",&a,&b,&m,&l,&ss);
    for(i=0;i<a+b;i++){
        for(j=0;j<a+b;j++)
            c[i][j]=d[i][j]=0;
        for(j=0;j<=ss;j++)
            to[j][i]=p[j][i]=0;
    }
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]=c[j][i]=k;
        d[i][j]=d[j][i]=k;
    }
    for(k=0;k<a;k++)
        for(i=0;i<a+b;i++)
            for(j=0;j<a+b;j++)
                if(c[i][k] && c[k][j]){
                    if(!c[i][j])c[i][j]=c[i][k]+c[k][j];
                    else c[i][j]<?=(c[i][k]+c[k][j]);
                }
    for(i=0;i<a+b;i++)
        for(j=0;j<a+b;j++)
            if(c[i][j]>l || !c[i][j])c[i][j]=0;
    to[0][0]=0;
    p[0][0]=1;
    for(k=0;k<=ss;k++)
        while(1){
            for(i=0;i<a+b && p[k][i]!=1;i++);
            if(i>=a+b)break;
            for(j=i+1;j<a+b;j++)
                if(p[k][j]==1 && to[k][j]<to[k][i])i=j;
            for(j=0;j<a+b;j++){
                if(d[i][j] && (!p[k][j] || to[k][i]+d[i][j]<to[k][j])){
                    p[k][j]=1;
                    to[k][j]=to[k][i]+d[i][j];
                }
                if(c[i][j]){
                    if(!p[k+1][j])
                        to[k+1][j]=to[k][i];
                    p[k+1][j]=1;
                    to[k+1][j]<?=to[k][i];
                }
            }
            p[k][i]=-1;
        }
    while(!p[ss][a+b-1])ss--;
    printf("%d\n",to[ss][a+b-1]);
}
}
