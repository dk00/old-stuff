#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
main(){
int i,j,n,tt,sn,step,t[9999],go1[9999],go2[9999],go3[9999];
scanf("%d",&tt);
while(tt--){
    scanf("%d",&n);
    for(step=sn=i=0;i<n;i++)scanf("%d",&t[i]);
    qsort(t,n,sizeof(t[0]),numcmp);
    if(n==0){
        if(tt)puts("");
        continue;
    }
    if(n==1){
        printf("%d\n%d\n",t[0],t[0]);
        if(tt)puts("");
        continue;
    }
    while(n>3){
        if(t[0]+t[n-2]<=2*t[1]){
            step+=t[n-1]+t[0];
            go1[sn]=t[0];
            go2[sn]=t[n-1];
            go3[sn++]=t[n-2];
            n--;
        }
        else{
            step+=t[0]+t[1];
            go1[sn]=t[0];
            go2[sn]=t[1];
            go3[sn++]=t[0];
            step+=t[n-1]+t[1];
            go1[sn]=t[n-2];
            go2[sn]=t[n-1];
            go3[sn++]=t[1];
            n--,n--;
        }
    }
    if(n==3){
        step+=t[2]+t[0];
        go1[sn]=t[0];
        go2[sn]=t[2];
        go3[sn++]=t[0];
        n--;
    }
    if(n==2){
        step+=t[1];
        go1[sn]=t[0];
        go2[sn++]=t[1];
    }
    printf("%d\n",step);
    for(n=0;n<sn;n++){
        printf("%d %d\n",go1[n],go2[n]);
        if(n<sn-1)printf("%d\n",go3[n]);
    }
}
}
/*
    1. z+a+y+a
    2. b+a+z+b
    2a+z+y<a+2b+z
    a+y<2b
*/
