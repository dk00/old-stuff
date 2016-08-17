#include<stdio.h>
#include<stdlib.h>
int v[32][2],c[15][32][32],use[15][32][32];
main(){
int i,j,k,l,n,t,s,C=1;
while(scanf("%d %d %d",&n,&t,&s) && t+n+s){
    v[0][0]=0;v[0][1]=0;
    v[t+1][0]=n-1;v[t+1][1]=n-1;
    for(i=1;i<=t;i++)
        scanf("%d %d",&v[i][0],&v[i][1]);
    for(i=0;i<=t+1;i++)
        for(j=0;j<=t+1;j++){
            c[0][i][j]=abs(v[i][0]-v[j][0])+abs(v[i][1]-v[j][1]);
            if(i!=0 && i!=t+1)use[0][i][j]|=(1<<i);
            if(j!=0 && j!=t+1)use[0][i][j]|=(1<<j);
        }
    for(l=1;l<=s;l++){
        for(i=0;i<=t+1;i++){
            for(j=0;j<=t+1;j++){
                c[l][i][j]=100000;
                use[l][i][j]=0;
            }
            c[l][i][i]=0;
        }
        for(i=0;i<=t+1;i++)
            for(j=0;j<=t+1;j++)
                for(k=0;k<=t+1;k++)
                    if(i!=k && j!=k && i!=j)
                        if((use[l-1][i][j]&(1<<k))==0 &&
                        c[l][i][j]>(c[l-1][i][k]+c[0][k][j])){
                            c[l][i][j]=(c[l-1][i][k]+c[0][k][j]);
                            use[l][i][j]=(use[l-1][i][j]|(1<<k));
                        }
    }
    printf("Case %d: %d\n",C++,c[s][0][t+1]);
}
}
