#include<stdio.h>
main(){
long c[30001][2],i,n;
for(i=0;i<=30000;i++){
    c[i][0]=1;
    c[i][1]=0;
}
for(i=0;i<=29995;i++){
    c[i+5][0]+=c[i][0];
    c[i+5][1]+=c[i][1];
    if(c[i+5][0]>=10000000){
        c[i+5][0]-=10000000;
        c[i+5][1]+=1;
    }
}
for(i=0;i<=29990;i++){
    c[i+10][0]+=c[i][0];
    c[i+10][1]+=c[i][1];
    if(c[i+10][0]>=10000000){
        c[i+10][0]-=10000000;
        c[i+10][1]+=1;
    }
}
for(i=0;i<=29975;i++){
    c[i+25][0]+=c[i][0];
    c[i+25][1]+=c[i][1];
    if(c[i+25][0]>=10000000){
        c[i+25][0]-=10000000;
        c[i+25][1]+=1;
    }
}
for(i=0;i<=29950;i++){
    c[i+50][0]+=c[i][0];
    c[i+50][1]+=c[i][1];
    if(c[i+50][0]>=10000000){
        c[i+50][0]-=10000000;
        c[i+50][1]+=1;
    }
}
while(scanf("%ld",&n)!=EOF){
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
