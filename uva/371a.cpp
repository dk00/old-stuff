#include<stdio.h>
int len(long long n){
int i;
    for(i=0;n!=1;i++){
        if(n%2)n=n*3+1;
        else n/=2;
    }
    return i;
}
main(){
long long l,h;
int k,max,v;
while(scanf("%lld %lld",&l,&h) && l+h){
    if(l>h){
        l+=h;
        h=l-h;
        l-=h;
    }
    printf("Between %lld and %lld, ",l,h);
    for(max=-1;l<=h;l++){
        k=len(l);
        if(l==1)k=3;
        if(k>max){
            v=l;
            max=k;
        }
    }
    printf("%d generates the longest sequence of %d values.\n",v,max);
}
}
