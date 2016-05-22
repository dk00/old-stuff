#include<stdio.h>
int l;
int _3n1(int n,int s){
    return n%2?n==1?s:n<=(l-1)/3?_3n1(n*3+1,s+1):s:_3n1(n>>1,s+1);
}
main(){
int a,C=1;
while(scanf("%d %d",&a,&l) && a>=0 && l>=0){
    printf("Case %d: A = %d, limit = %d, number of terms = %d\n",
    C++,a,l,_3n1(a,1));
}
}
