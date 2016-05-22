#include<stdio.h>
#include<stdlib.h>
inline void polyshow(int c,int p){
    c=abs(c);
    if(c>1)printf("%d",c);
    if(p)putchar('x');
    else if(c==1)printf("%d",c);
    if(p>1)printf("^%d",p);
}
main(){
int i,c[10];
while(scanf("%d",&c[0])!=EOF){
    for(i=1;i<9;i++)scanf("%d",&c[i]);
    for(i=0;!c[i] && i<8;i++);
    if(c[i]<0)putchar('-');
    polyshow(c[i],8-i);
    for(i++;i<9;i++){
        if(!c[i])continue;
        printf(" %c ",c[i]>0?'+':'-');
        polyshow(c[i],8-i);
    }
    puts("");
}
}
