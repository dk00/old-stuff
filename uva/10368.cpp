#include<stdio.h>
int winlose1(int a,int b);
int winlose2(int a,int b);
main(){
int a,b;
while(scanf("%d %d",&a,&b) && a && b)
    puts(winlose1(a>?b,a<?b)?"Stan wins":"Ollie wins");
}
inline int winlose1(int a,int b){
    if(a%b==0)return 1;
    if(winlose2(b,a%b))return 1;
    for(int i=a%b+b;i<a;i+=b)
        if(winlose2(i,b))return 1;
    return 0;
}
inline int winlose2(int a,int b){
    if(a%b==0)return 0;
    if(!winlose1(b,a%b))return 0;
    for(int i=a%b+b;i<a;i+=b)
        if(!winlose1(i,b))return 0;
    return 1;
}
