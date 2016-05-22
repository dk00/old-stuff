// 5 10 20 50 100 200 500 1000 2000 5000 10000
// 1  2  4 10  20  40 100  200  400 1000  2000
#include<stdio.h>
main(){
long c[6001][2],i,n;
for(i=0;i<=6000;i++){
    c[i][0]=1;
    c[i][1]=0;
}
for(i=0;i<=5998;i++){
    c[i+2][0]+=c[i][0];
    c[i+2][1]+=c[i][1];
    if(c[i+2][0]>=100000000){
        c[i+2][0]-=100000000;
        c[i+2][1]+=1;
    }
}
for(i=0;i<=5996;i++){
    c[i+4][0]+=c[i][0];
    c[i+4][1]+=c[i][1];
    if(c[i+4][0]>=100000000){
        c[i+4][0]-=100000000;
        c[i+4][1]+=1;
    }
}
for(i=0;i<=29975;i++){
    c[i+25][0]+=c[i][0];
    c[i+25][1]+=c[i][1];
    if(c[i+25][0]>=100000000){
        c[i+25][0]-=100000000;
        c[i+25][1]+=1;
    }
}
for(i=0;i<=29950;i++){
    c[i+50][0]+=c[i][0];
    c[i+50][1]+=c[i][1];
    if(c[i+50][0]>=100000000){
        c[i+50][0]-=100000000;
        c[i+50][1]+=1;
    }
}
while(scanf("%ld.%ld",&n,&i)!=EOF){
    n=(n*100+1)/5;
    if(c[n][0]==1) printf(
    "There is only 1 way to produce %ld cents change.\n",n);
    else{
        printf("There are ");
        if(c[n][1]>=1)printf("%ld%07ld",c[n][1],c[n][0]);
        else printf("%ld",c[n][0]);
        printf(" ways to produce %ld cents change.\n",n);
    }
}
}
