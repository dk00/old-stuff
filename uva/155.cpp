#include<stdio.h>
#include<stdlib.h>
int x,y,c;
void inline r(int cx,int cy,int k){
    if(abs(cx-x)<=k && abs(cy-y)<=k)c++;
    if(k<=1)return;
    r(cx-k,cy-k,k>>1);
    r(cx-k,cy+k,k>>1);
    r(cx+k,cy-k,k>>1);
    r(cx+k,cy+k,k>>1);
}
main(){
int k;
while(scanf("%d %d %d",&k,&x,&y)&&k+x+y)
    printf("%3d\n",(c=0,r(1024,1024,k),c));
}
