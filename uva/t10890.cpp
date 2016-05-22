#include<time.h>
#include<stdio.h>
#include<stdlib.h>
int const n=5,t=4;
int px[100],py[100],map[50][50];
main(){
srand(time(NULL));
freopen("10890.in","w",stdout);
int i,j,k,r,s;
for(r=0;r<10;r++){
    printf("%d %d %d\n",n,t,rand()%t+1);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)map[i][j]=0;
    for(i=0;i<t;i++){
        while(1){
            j=rand()%n;
            k=rand()%n;
            if(j && k && (j!=n-1 || k!=n-1) && !map[j][k]){
                printf(" %d %d",j,k);
                map[j][k]=1;
                break;
            }
        }
    }
    puts("");
}
puts("0 0 0");
}
