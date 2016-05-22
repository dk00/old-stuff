#include<stdio.h>
inline long long af(long long n){
long long i;
    for(i=0;n!=1;i++)
        if(n%2)n=n*3+1;
        else n/=2;
    return i;
}
main(){
long long k,l,h,max,num;
while(scanf("%lld %lld",&l,&h) && l+h){
    printf("Between %lld and %lld, ",l,h);
    if(l>h){
        l+=h;
        h=l-h;
        l-=h;
    }
    for(max=0;l<=h;l++){
        k=af(l);
        if(k>max){
            max=k;
            num=l;
        }
    }
    printf("%lld generates the longest sequence of %lld values.\n",num,max);
}
}
