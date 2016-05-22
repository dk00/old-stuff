#include<stdio.h>
int op;
int key[500000],tmp[500000];
void msort(int s,int e){
    if(s>=e)return;
    int m=(s+e)/2,p1,p2,p;
    msort(p=p1=s,m);
    msort(p2=m+1,e);
    while(p<=e){
        if(p1>m)key[p++]=tmp[p2++];
        else if(p2>e)key[p++]=tmp[p1++];
        else if(tmp[p1]>tmp[p2]){
            key[p++]=tmp[p2++];
            op+=m-p1+1;
        }
        else key[p++]=tmp[p1++];
    }
    for(;s<=e;s++)tmp[s]=key[s];
}
main(){
    int i,n;
    while(scanf("%d",&n) && n){
        for(i=0;i<n;i++)scanf("%d",&tmp[i]);
        msort(op=0,n-1);
        printf("%d\n",op);
    }
}
