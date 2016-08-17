#include<stdio.h>
#include<stdlib.h>
int map[75],s1[7][75],s2[7][75];
int inf=2000000000;
main(){
int i,j,k,n,m,now,C=1;
while(scanf("%d %d",&n,&m) && n+m){
    if(n==1)abort();
    for(k=0;k<=m;k++)
        for(i=0;i<n;i++)
            s1[k][i]=s2[k][i]=-inf;
    s1[0][0]=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            scanf("%d",&map[j]);
        for(k=0;k<=m;k++){
            for(j=0,now=-inf;j<n;j++){
                if(s1[k][j]>-inf)
                    now>?=s1[k][j];
                if(now<=-inf)continue;
                if(j+1<n && map[j+1]<0)
                    s1[k+1][j+1]>?=now;
                now+=map[j];
                if(map[j]<0){
                    s2[k+1][j]>?=now;
                    now=-inf;
                }
                else
                    s2[k][j]>?=now;
            }
            for(j=n-1,now=-inf;j>=0;j--){
                if(s1[k][j]>-inf)
                    now>?=s1[k][j];
                if(now<=-inf)continue;
                if(j && map[j+1]<0)
                    s1[k+1][j-1]>?=now;
                now+=map[j];
                if(map[j]<0){
                    s2[k+1][j]>?=now;
                    now=-inf;
                }
                else
                    s2[k][j]>?=now;
            }
        }
        for(k=0;k<=m;k++)
            for(j=0;j<n;j++){
                s1[k][j]=s2[k][j];
                s2[k][j]=-inf;
            }
    }
    for(now=-inf,k=0;k<=m;k++)
        if(s1[k][n-1]>-inf)
            now>?=s1[k][n-1];
    if(now>-inf)
        printf("Case %d: %d\n",C++,now);
    else
        printf("Case %d: impossible\n",C++);
}
}
