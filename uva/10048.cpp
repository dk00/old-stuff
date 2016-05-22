#include<stdio.h>
long p[1001][1001];
main(){
long c,s,q,i,j,k,ca=0;
while(scanf("%ld %ld %ld",&c,&s,&q)){
    if(!c && !s && !q)break;
    for(i=1;i<=c;i++)
        for(j=1;j<=c;j++)p[i][j]=2147483647;
    while(s--){
        scanf("%ld %ld %ld",&i,&j,&k);
        p[i][j]=p[j][i]=k;
    }
    for(k=1;k<=c;k++)
        for(i=1;i<=c;i++)
            for(j=1;j<=c;j++)p[i][j]<?=(p[i][k]>?p[k][j]);
    if(ca)puts("");
    printf("Case #%ld\n",++ca);
    while(q--){
        scanf("%ld %ld",&i,&j);
        if(p[i][j]<2147483647)printf("%ld\n",p[i][j]);
        else puts("no path");
    }
}
}
