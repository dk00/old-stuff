#include<stdio.h>
void gcd(int a,int b,int p,int q,int r,int s){
    if(a%b){
        gcd(b,a%b,r,s,p-r*(a/b),q-s*(a/b));
    }
    else{
        printf("%d %d %d\n",r,s,b);
        return;
    }
}
main(){
int a,b;
while(scanf("%d %d",&a,&b)!=EOF)gcd(a,b,1,0,0,1);
}
