#define Size 10000
#define Default 0
#include"bigint0.h"
main(){
freopen("test!.out","w",stdout);
bigint a,b;
int i,j;
a=3;
b=3;
for(j=2,i=18;i--;j+=j){
    printf("3^%d\n",j);
    a=a*b;
    b=a;
    a.show();
}

}
