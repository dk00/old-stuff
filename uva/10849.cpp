#include<stdio.h>
main(){
int c,n,t,bx,by,tx,ty;
scanf("%d",&c);
while(c--){
    scanf("%d %d",&t,&n);
    while(t--){
        scanf("%d %d %d %d",&bx,&by,&tx,&ty);
        if((bx%2+by%2+tx%2+ty%2)%2)puts("no move");
        else if(tx>n || ty>n)puts("no move");
        else if(tx==bx && ty==by)puts("0");
        else if(tx+ty==bx+by || bx-by==tx-ty)puts("1");
        else puts("2");
    }
}
}
