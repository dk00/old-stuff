#include<stdio.h>
int main(){
int a,b,t;
while(scanf("%ld %ld",&a,&b)!=EOF){
    printf("[%ld;",a/b);
    a%=b;
    printf("%ld",b/a);
    while(a>b?a%=b:b%=a){
        if(a>b)printf(",%ld",a/b);
        else printf(",%ld",b/a);
    }
    puts("]");
}
}
