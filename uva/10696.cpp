#include <stdio.h>
int f91(int i);
int main(){
    int n;
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        printf("f91(%d) = %d\n",n,f91(n));
    }
    return 0;
}
int f91(int n){
    if(n<=100)
        return f91(f91(n+11));
    return n-10;
}
