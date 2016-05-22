#include <stdio.h>

int main(){
    long long fac=1, i, k;
    while(scanf("%I64d", &k)!=EOF){
        i=(k-1940)/10;
        for(k=1;k<=i;k++)
            fac*=2;
        for(k=1,i=1;k<=254020;k++){
            i*=k;
            if(i>fac)
            break;
        }
        printf("%I64d\n", k-1);
    }
    return 0;
}
