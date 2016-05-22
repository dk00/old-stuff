#include<stdio.h>
long link[1001][1001],max[1001],to[1001];
main(){
long n,r,i,j,min,c1,c2,p,sc=0;
while(scanf("%ld %ld",&n,&r) && n && r){
    for(i=1;i<=n;i++){
        max[i]=0;
        for(j=1;j<=n;j++)link[i][j]=0;
    }
    while(r-- && scanf("%ld %ld %ld",&c1,&c2,&p)){
        link[c1][c2]>?=p;
        link[c2][c1]=link[c1][c2];
        if((c1<1&&c1>n)||c2<1&&c2>n||p<1)break;
    }
    if((c1<1&&c1>n)||c2<1&&c2>n||p<1)break;
    for(i=1;i<=n;i++){
        max[i]=0;
        to[i]=link[p][i];
    }
    scanf("%ld %ld %ld",&c1,&c2,&p);
    for(i=1;i<=n;i++)to[i]=link[c1][i];
    max[c1]=2147483647;
    for(i=n-1;i-- && max[c2]<=0;){
        for(j=1;max[j];j++);
        min=j;
        for(j++;j<=n;j++)
            if(!max[j] && to[j]>to[min])min=j;
        max[min]=to[min];
        for(j=1;j<=n;j++)
            if(!max[j])to[j]>?=link[min][j]<?max[min];
    }
    //if(sc)puts("");
    max[c2]--;
    printf("Scenario #%ld\nMinimum Number of Trips = ",++sc);
    printf("%ld\n\n",p/max[c2]+(p%max[c2]>0));
}
}
